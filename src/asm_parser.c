/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:39:49 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/10 12:49:27 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		automate_syn(t_token *token, int state)
{
	int	i;
	int	new_state;

	i = -1;
	while (++i < 12)
	{
		if (token->lexem == g_index_col_syn[i])
			break ;
	}
	new_state = g_automate_syn[state][i];
	return (new_state);
}

static int		state_manager_parser(t_instr **instructions,\
		t_instr **instruction, t_token *token, int *state)
{
	int	tmp;

	tmp = *state;
	if ((*state = automate_syn(token, *state)) == -1)
		return (print_syn_error(token->line, token->col, token->lexem, tmp));
	if (*state == 1 || (*state == 3 && token->lexem == COMMENT))
	{
		if (!(*instruction = create_instruction(token)))
			return (-1);
		append_inst(instructions, *instruction);
	}
	if (tmp == 4 && *state != 4 && (*instruction && (*instruction)->params))
	{
		if (!(*instruction = create_instruction(token)))
			return (-1);
		append_inst(instructions, *instruction);
	}
	if (*state == 6)
	{
		*state = 6 + ft_atoi(token->value);
		if (tmp == 4 || tmp == 5)
			(*instruction)->opcode = ft_atoi(token->value);
	}
	return (0);
}

int				check_label(t_token *token, t_token *labels)
{
	if (token->lexem == LABEL)
	{
		while (labels)
		{
			if (!ft_strcmp(token->value, labels->value))
				if (token->col != labels->col || token->line != labels->line)
					return (print_dup_label_error(token, labels));
			labels = labels->next;
		}
	}
	else if (*(token->value) == ':')
	{
		while (labels)
		{
			if (!ft_strcmp(token->value + 1, labels->value))
				break ;
			labels = labels->next;
		}
		if (!labels)
			return (print_label_error(token));
	}
	return (0);
}

int				check_token(t_token *token, t_token *labels)
{
	int	tmp;

	if (token->lexem == COMMENT || token->lexem == NAME)
	{
		tmp = token->lexem == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH;
		if ((int)ft_strlen(token->value) > tmp)
			return (print_len_error(token, tmp));
	}
	else if (token->lexem == REGISTER)
	{
		if (verif_int(token->value, 1, 16, 2))
			return (print_int_error(token, 1, 16));
	}
	else if (token->lexem == LABEL || *(token->value) == ':')
		if (check_label(token, labels))
			return (1);
	return (0);
}

int				parser_asm(t_token **tokens, t_instr **instructions,\
		t_token *labels)
{
	t_token	*tmp;
	t_instr	*instruction;
	int		state;
	int		ret;

	state = 0;
	ret = 0;
	instruction = NULL;
	if (!*tokens)
		return (print_syn_error(1, 1, NONE, state));
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if (check_token(*tokens, labels))
			return (1);
		if ((ret = state_manager_parser(instructions, &instruction, *tokens,\
						&state)))
			return (ret);
		if ((!tmp && (state != 4 || !instruction || (instruction->params\
							&& instruction->params->lexem == COMMENT))))
			ret = print_syn_error((*tokens)->line, (*tokens)->col, NONE, state);
		complete_instruction(&instruction, *tokens);
		*tokens = tmp;
	}
	return (ret ? ret : 0);
}

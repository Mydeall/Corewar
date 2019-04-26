/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:52:33 by rkirszba          #+#    #+#             */
/*   Updated: 2019/04/26 18:27:24 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		automate_syn(t_token *token,int state)
{
	int	i;
	int	new_state;

	i = -1;
	while (++i < 12)
	{
		if ((token->lexem == g_index_col_syn[i]))
			break ;
	}
	new_state = g_automate_syn[state][i];
	return (new_state);
}

t_instr	*create_instruction(t_token *token)
{
	t_instr *new;

	if (!(new = (t_instr*)malloc(sizeof(t_instr))))
		return (NULL);
	if (token->lexem == OPCODE)
		new->opcode = ft_atoi(token->value);
	else
		new->opcode = 0;
	new->params = NULL;
	if (token->lexem == LABEL)
	{
		if (!(new->label = ft_strdup(token->value)))
		{
			free(new);
			return (NULL);
		}
	}
	else
		new->label = NULL;
	new->next = NULL;
	return (new);
}

int		print_syn_error(t_token *token, int state)
{
	(void)token;
	(void)state;
}
int		print_len_error(t_token *token)
{
	(void)token;
	return (1);
}

void	append_inst(t_instr **instructions, t_instr *instruction)
{
	t_instr	*current;

	current = *instructions;
	if (!(*instructions))
	{
		*instructions = instruction;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = instruction;
}	

int		state_manager(t_instr **instructions, t_instr **instruction,
		t_token *token, int *state)
{
	int	ret;
	int	tmp;
	
	tmp = *state;
	if ((*state = automate_syn(token, state)) == -1)
		return (print_syn_error(token, *state));
	if (*state == 1 || (*state == 3 && token->lexem == COMMENT))
	{
		if (ft_strlen(token->value) > state == 1 ? PROG_NAME_LENGTH
				: COMMENT_LENGTH)
			return (print_len_error(token));
		if (!(*instruction = create_instruction(token)))
			return (-1);
		append_inst(instructions, *instruction);
	}
	if (tmp == 4 && *state != 4)
	{
		if (!(*instruction = create_instruction(token)))
			return (-1);
		append_inst(instructions, *instruction);
	}
	if (*state == 6)
	{
		*state = 6 + ft_atoi(token->value);
		if (tmp == 5)
			(*instruction)->opcode = ft_atoi(token->value);
	}
	return (0);
}

static void	complete_instruction(t_instr **instruction, t_token *token)
{	
	t_token	*current;	
	
	if (token->lexem != NAME || token->lexem != COMMENT || token->lexem != DIRECT\
			|| token->lexem != REGISTER || token->lexem != INDIRECT)
	{
		free_token(token);
		return ;
	}
	token->next = NULL;
	if (!(*instruction)->params)
	{
		(*instruction)->params = token;
		return ;
	}
	current = (*instruction)->params;
	while (current->next)
		current = current->next;
	current->next = token;
	return ;
}

int		parser_asm(t_token **tokens, t_instr **instructions, t_label *labels)
{
	t_token	*tmp;
	t_instr	*instruction;
	int		state;
	int		ret;

	state = 0;
	instruction = NULL;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((ret = state_manager(instructions, &instruction, *tokens,\
						&state)))
			return (ret);
		complete_instruction(instruction, *tokens);
		*tokens = tmp;
	}
	return (0);
}

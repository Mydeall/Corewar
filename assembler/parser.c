/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:52:33 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/06 19:57:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		automate_syn(t_token *token,int state)
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

static t_instr	*create_instruction(t_token *token)
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

static void	append_inst(t_instr **instructions, t_instr *instruction)
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

static int		state_manager_parser(t_instr **instructions, t_instr **instruction,
		t_token *token, int *state)
{
	int	tmp;
	
	tmp = *state;
	if ((*state = automate_syn(token, *state)) == -1)
		return (print_syn_error(token, tmp));
	if (*state == 1 || (*state == 3 && token->lexem == COMMENT))
	{
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
	
	if (token->lexem != NAME && token->lexem != COMMENT && token->lexem != DIRECT\
			&& token->lexem != REGISTER && token->lexem != INDIRECT)
	{
		free_token(&token);
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

int			verif_int(char *str, int min, int max, int size)
{
	int				len;
	int				i;
	long long int	nb;

	i = *str == '-' ? 1 : 0;
	while (str[i] == '0' && str[i])
		i++;
	i = str[i] == 0 ? i - 1 : i;
	len = -1;
	while (str[++len + i])
		if (len > size)
			return (1);
	nb = ft_atoi(str);
	if (nb >= min && nb <= max)
		return (0);
	return (1);
}

int		check_label(t_token *token, t_token *labels)
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
				break;
			labels = labels->next;
		}
		if (!labels)
			return (print_label_error(token));
	}
	return (0);
}

int		check_token(t_token *token, t_token *labels)
{
	int 	tmp;

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

int		parser_asm(t_token **tokens, t_instr **instructions, t_token *labels)
{
	t_token	*tmp;
	t_instr	*instruction;
	int		state;
	int		ret;

	state = 0;
	instruction = NULL;
	check_tokens(*tokens);
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if (check_token(*tokens, labels))
			return (1);
		if ((ret = state_manager_parser(instructions, &instruction, *tokens,\
						&state)))
			return (ret);
		complete_instruction(&instruction, *tokens);
		if (!tmp && state != 4)
			ret = print_syn_error(tmp, state);
		*tokens = tmp;
	}
	return (ret ? ret : 0);
}

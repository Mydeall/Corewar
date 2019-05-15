/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:40:12 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 17:40:27 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	new->label = NULL;
	new->next = NULL;
	return (new);
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

void	complete_instruction(t_instr **instruction, t_token *token)
{
	if (token->lexem == COMMA || token->lexem == OPCODE\
			|| token->lexem == CARRIAGE)
	{
		free_token(&token);
		return ;
	}
	token->next = NULL;
	if (token->lexem == LABEL)
		append_token(&((*instruction)->label), token);
	else
		append_token(&((*instruction)->params), token);
}

int		verif_int(char *str, int min, int max, int size)
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

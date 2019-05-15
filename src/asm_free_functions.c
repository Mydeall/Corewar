/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:38:48 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 17:38:58 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_token(t_token **token)
{
	if ((*token)->value)
		ft_strdel(&(*token)->value);
	free(*token);
	*token = NULL;
}

void	free_instruction(t_instr **instruction)
{
	t_token	*tmp;

	if (!(*instruction))
		return ;
	while ((*instruction)->label)
	{
		tmp = (*instruction)->label;
		(*instruction)->label = (*instruction)->label->next;
		free_token(&tmp);
	}
	while ((*instruction)->params)
	{
		tmp = (*instruction)->params;
		(*instruction)->params = (*instruction)->params->next;
		free_token(&tmp);
	}
	free(*instruction);
	*instruction = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free_token(&tmp);
	}
	*tokens = NULL;
}

int		free_manager(t_token *tokens, t_instr *instructions,\
		t_token *labels, int fd)
{
	t_token	*tmp;
	t_instr	*tmp2;

	free_tokens(&tokens);
	while (labels)
	{
		tmp = labels;
		labels = labels->next;
		free_token(&tmp);
	}
	while (instructions)
	{
		tmp2 = instructions;
		instructions = instructions->next;
		free_instruction(&tmp2);
	}
	if (close(fd))
		return (print_sys_error(errno));
	return (0);
}

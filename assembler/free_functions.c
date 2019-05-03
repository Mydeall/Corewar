/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:46:33 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/03 12:46:28 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_token(t_token **token)
{
	ft_strdel(&(*token)->value);
	free(*token);
	*token = NULL;
}

void	free_instruction(t_instr **instruction)
{
	t_token	*tmp;

	ft_strdel(&(*instruction)->label);
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
void	free_manager(t_token *tokens, t_instr *instructions, t_token *labels)
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
}

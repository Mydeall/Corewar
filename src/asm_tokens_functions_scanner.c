/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tokens_functions_scanner.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:43:00 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 18:42:54 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*get_back_token(t_token **tokens)
{
	t_token *current;
	t_token	*tmp;

	if (!*tokens)
		return (NULL);
	current = *tokens;
	tmp = NULL;
	while (current->next)
	{
		tmp = current;
		current = current->next;
	}
	if (current->lexem == NONE)
	{
		if (tmp)
			tmp->next = NULL;
		else
			*tokens = NULL;
		return (current);
	}
	return (NULL);
}

int			complete_token(t_token *token, int state, t_reader *reader)
{
	int		ret;

	if (token)
	{
		token->lexem = state;
		if ((ret = create_value(token, reader)))
		{
			free(token);
			return (ret);
		}
		ft_strdel(&(reader->rest));
	}
	return (0);
}

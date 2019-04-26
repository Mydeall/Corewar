/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:58:33 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/26 11:28:34 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_token(t_token **token)
{
	ft_strdel(&(*token)->value);
	free(*token);
	*token = NULL;
}

int		create_token(t_token **token, t_reader *reader, int start)
{
	*token = NULL;
	if (!reader->buff[start])
		return (0);
	if (!(*token = (t_token*)malloc(sizeof(t_token))))
		return (1);
	(*token)->lexem = NONE;
	(*token)->value = reader->buff + start;
	(*token)->line = reader->state == 6 ? reader->line + 1 : reader->line;
	(*token)->col = reader->state == 6 ? 1 : reader->col;
	(*token)->next = NULL;
	return (0);
}

int		complete_token(t_token *token, int state, t_reader *reader)
{
	int		ret;

	if (g_automate[state][0] == -2 || g_automate[state][0] == -3)
	{
		token->lexem = state;
		if ((ret = create_value(token, reader)))
		{
			free(token);
			return (ret);
		}
	}
	else
		token->value = reader->buff;
	return (0);
}

int		append_token(t_token **tokens, t_token *token, int state, t_reader *reader)
{
	t_token *current;
	int		ret;

	if (!token)
		return (0);
	if ((ret = complete_token(token, state, reader)))
		return (ret);
	if (!*tokens)
	{
		*tokens = token;
		return (0);
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = token;
	return (0);
}

t_token	*get_back_token(t_token **tokens)
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

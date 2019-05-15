/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tokens_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:42:18 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 17:42:43 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*create_token(char *value, t_reader *reader, int shift)
{
	t_token	*token;

	if (!(token = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	token->lexem = NONE;
	token->value = value;
	token->line = reader->state == 6 ? reader->line + 1 : reader->line;
	token->col = reader->state == 6 ? 1 : reader->col + shift;
	token->address = 0;
	token->inst_address = 0;
	token->next = NULL;
	return (token);
}

t_token		*create_label(t_token *token, t_writer *writer,\
		unsigned int inst_address, int size)
{
	t_token	*cp;

	token->address = writer->address + writer->cursor;
	token->size = size;
	token->inst_address = inst_address;
	if (!(cp = copy_token(token)))
		return (NULL);
	while (size--)
		writer->buff[writer->cursor++] = 0;
	return (cp);
}

void		append_token(t_token **tokens, t_token *token)
{
	t_token *current;

	if (!token)
		return ;
	if (!*tokens)
	{
		*tokens = token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = token;
}

t_token		*copy_token(t_token *token)
{
	t_token *new;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	if (!(new->value = ft_strdup(token->value)))
	{
		free(new);
		return (NULL);
	}
	new->lexem = token->lexem;
	new->line = token->line;
	new->col = token->col;
	new->size = token->size;
	new->address = token->address;
	new->inst_address = token->inst_address;
	new->next = NULL;
	return (new);
}

void		remove_token(t_token **tokens, t_token *token)
{
	t_token	*tmp;

	if (*tokens == token)
	{
		*tokens = NULL;
		free_token(&token);
		return ;
	}
	tmp = *tokens;
	while (tmp->next != token)
		tmp = tmp->next;
	tmp->next = NULL;
	free_token(&token);
}

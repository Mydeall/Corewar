/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:58:33 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/01 13:43:29 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		create_token(t_token **token, t_reader *reader, int shift)
{
	*token = NULL;
	if (reader->cursor + shift == reader->nb_chars)
		return (0);
	if (!(*token = (t_token*)malloc(sizeof(t_token))))
		return (1);
	(*token)->lexem = NONE;
	(*token)->value = &reader->buff[reader->cursor + shift];
	(*token)->line = reader->state == 6 ? reader->line + 1 : reader->line;
	(*token)->col = reader->state == 6 ? 1 : reader->col + shift;
	(*token)->address = 0;
	(*token)->next = NULL;
	return (0);
}

int		complete_token(t_token *token, int state, t_reader *reader)
{
	int		ret;

	if (g_automate_lex[state][0] == -2 || g_automate_lex[state][0] == -3)
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

int		append_label(t_token *token, t_token **labels)
{
	t_token *current;
	t_token *label;

	if (!(label = (t_token*)malloc(sizeof(t_token))))
		return (1);
	if (!(label->value = ft_strdup(token->value)))
	{
		free(label);
		return (1);
	}
	label->line= token->line;
	label->col= token->col;
	label->address = 0;
	label->next = NULL;
	if (!*labels)
	{
		*labels = label;
		return (0);
	}
	current = *labels;
	while (current->next)
		current = current->next;
	current->next = label;
	return (0);
}


int		append_queue(t_token **queue, t_token *token)
{
	t_token	*new;
	t_token	*current;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (1);
	if (!(new->value = ft_strdup(token->value)))
	{
		free(new);
		return (1);
	}
	new->lexem = token->lexem;
	new->address = token->address;
	new->next = NULL;
	if (!(*queue))
	{
		*queue = new;
		return (0);
	}
	current = *queue;
	while (current->next)
		current = current->next;
	current->next = new;
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

/*
printf("-------- create token ---------\n");
	printf("reader->pointeur : |%c|\n", (reader->buff)[reader->cursor]);
	printf("shift: |%d|\n", shift);
	printf("start value : |%c|\n", reader->buff[reader->cursor + shift]);
	printf("reader->line: |%d|\n", reader->line);
	printf("reader->col: |%d|\n", reader->col);
	printf("token->line: |%d|\n", (*token)->line);
	printf("token->col: |%d|\n", (*token)->col);
*/

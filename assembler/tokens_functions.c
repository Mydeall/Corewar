/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:58:33 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/03 18:19:04 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token	*create_token(char *value, t_reader *reader, int shift)
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

int		complete_token(t_token *token, int state, t_reader *reader)
{
	int		ret;

	printf("-------- complete -------\n");
//	print_token(token);
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
	printf("-------------------------\n");
	return (0);
}

void	append_token(t_token **tokens, t_token *token)
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

t_token	*copy_token(t_token *token)
{
	t_token *new;
//
	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	if (!(new->value = ft_strdup(token->value)))
	{
		free(new);
		return (NULL);
	}
	new->lexem = token->lexem;
	new->line= token->line;
	new->col= token->col;
	new->size = token->size;
	new->address = token->address;
	new->inst_address = token->inst_address;
	new->next = NULL;
	return (new);
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

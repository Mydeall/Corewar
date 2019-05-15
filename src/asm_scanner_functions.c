/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_scanner_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:41:53 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/15 15:08:47 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	automate(char c, int state)
{
	int		i;
	int		new_state;
	char	*ret;

	i = -1;
	while (++i < 12)
	{
		if (c == 0)
		{
			i = 12;
			break ;
		}
		if ((ret = ft_strchr(g_index_col_lex[i], c)))
			break ;
	}
	new_state = g_automate_lex[state][i];
	return (new_state);
}

int	token_manager(t_token **token, t_token **tokens, t_reader *reader,\
		t_token **labels)
{
	t_token *new;

	append_token(tokens, *token);
	if (*token && (*token)->lexem == LABEL)
	{
		if (!(new = copy_token(*token)))
			return (1);
		append_token(labels, new);
	}
	*token = NULL;
	if (!(*token = create_token(&(reader->buff[reader->cursor + 1]),\
					reader, 1)))
		return (1);
	return (0);
}

int	state_manager_scan(t_token **tokens, t_token **token,\
		t_reader *reader, t_token **labels)
{
	int ret;

	if (reader->state == -1)
	{
		free(*token);
		return (print_lex_error(reader->line, reader->col));
	}
	if (g_automate_lex[reader->state][0] == -2\
			|| g_automate_lex[reader->state][0] == -3)
	{
		if (g_automate_lex[reader->state][0] == -3)
		{
			(reader->cursor)--;
			(reader->col)--;
		}
		if ((ret = complete_token(*token, reader->state, reader)))
			return (ret);
		if (token_manager(token, tokens, reader, labels))
			return (-1);
		reader->state = 0;
	}
	return (0);
}

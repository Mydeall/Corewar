/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_scanner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:40:42 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/15 15:11:46 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	manage_last_token(t_reader *reader, t_token **tokens)
{
	t_token *token;
	int		ret;

	if (!(token = get_back_token(tokens))\
			|| g_automate_lex[token->lexem][0] == -2\
			|| g_automate_lex[token->lexem][0] == -3)
		return (0);
	if (reader->state != 0)
		reader->state = automate('\n', reader->state);
	if (g_automate_lex[reader->state][0] != -2\
			&& g_automate_lex[reader->state][0] != -3)
	{
		token->value = NULL;
		free_token(&token);
		return (reader->state ? print_lex_error(reader->line, reader->col) : 0);
	}
	(reader->cursor)--;
	if ((ret = complete_token(token, reader->state, reader)))
	{
		token->value = NULL;
		free_token(&token);
		return (ret);
	}
	append_token(tokens, token);
	return (0);
}

static int	manage_end_buffer(t_reader *reader, t_token **tokens,\
		t_token *token)
{
	int ret;

	if (g_automate_lex[reader->state][0] != -2\
			&& g_automate_lex[reader->state][0] != -3\
			&& reader->cursor == BUFF_SIZE_ASM)
	{
		if (ft_strnappend(&(reader->rest), token->value,\
					reader->buff + reader->cursor - token->value))
			return (-1);
		token->value = reader->buff;
	}
	else if (g_automate_lex[reader->state][0] == -2\
			|| g_automate_lex[reader->state][0] == -3)
	{
		if ((ret = complete_token(token, reader->state, reader)))
			return (ret);
	}
	append_token(tokens, token);
	return (0);
}

static int	buff_manager(t_reader *reader, t_token **tokens,\
		t_token **labels)
{
	t_token		*token;
	int			ret;

	if (!(token = get_back_token(tokens)))
		if (!(token = create_token(&(reader->buff[reader->cursor]), reader, 0)))
			return (-1);
	while (reader->cursor < reader->nb_chars)
	{
		reader->state = automate(reader->buff[reader->cursor], reader->state);
		if ((ret = state_manager_scan(tokens, &token, reader, labels)))
			return (ret);
		if (reader->cursor >= 0 && reader->buff[reader->cursor] == '\n')
		{
			(reader->line)++;
			reader->col = 0;
		}
		if (reader->cursor >= 0)
			reader->col = reader->buff[reader->cursor] == '\t' ? reader->col + 4 :
				reader->col + 1;
		(reader->cursor)++;
	}
	if ((ret = manage_end_buffer(reader, tokens, token)))
		return (ret);
	return (0);
}

int			scanner_asm(int fd, t_token **tokens, t_token **labels)
{
	t_reader	reader;
	int			ret;

	reader.line = 1;
	reader.col = 1;
	reader.state = 0;
	reader.rest = NULL;
	while ((reader.nb_chars = read(fd, reader.buff, BUFF_SIZE_ASM)))
	{
		if (reader.nb_chars == -1)
			return (-1);
		reader.cursor = 0;
		if ((ret = buff_manager(&reader, tokens, labels)))
		{
			ft_strdel(&(reader.rest));
			return (ret);
		}
	}
	ret = manage_last_token(&reader, tokens);
	ft_strdel(&(reader.rest));
	return (ret);
}

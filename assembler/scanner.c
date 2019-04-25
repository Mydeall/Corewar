/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:56:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/25 18:01:34 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//create value --> trimchar(espacement/%/:) + si token --> decoupage spe

static int		automate(char c, int state)
{
	int	i;
	int	new_state;
	char *ret;

	i = -1;
	printf("char to find : %c\n", c);
	while (++i < 12)
	{
		if ((ret = ft_strchr(g_index_col[i], c)))
			break ;
	}
	if (ret)
		printf("char found : %c\n", *ret);
	new_state = g_automate[state][i];
	printf("new state : %d\n", new_state);
	return (new_state);
}

static int		state_manager(t_token **tokens, t_token **token,\
		t_reader *reader, int *state)
{
	int ret;

	if (*state == -1)
	{
		free(*token);
		return (print_lex_error(reader->line, reader->col));
	}
	if (g_automate[*state][0] == -2 || g_automate[*state][0] == -3)
	{
		printf("final state\n");
		if (g_automate[*state][0] == -3)
		{
			(reader->cursor)--;
			(reader->col)--;
		}
		if ((ret = append_token(tokens, *token, *state, reader)))
			return (ret);
		if ((create_token(token, reader, reader->cursor + 1)))
			return (-1);
		*state = 0;
	}
	return (0);
}

static int		buff_manager(t_reader *reader, t_token **tokens)
{
	t_token		*token;
	int			ret;

	if (!(token = get_back_token(tokens)))
		if ((create_token(&token, reader, 0)))
			return (-1);
	while (reader->cursor < reader->nb_chars)
	{
		printf("-------------------------\n");
		printf("state = %d\n", reader->state);
		reader->state = automate(reader->buff[reader->cursor], reader->state);
		if ((ret = state_manager(tokens, &token, reader, &(reader->state))))
			return (ret);
		if (reader->cursor >= 0 && reader->buff[reader->cursor] == '\n')
		{
			(reader->line)++;
			reader->col = 0;
		}
		(reader->col)++;
		(reader->cursor)++;
	}
	printf("FIN DE BUFFER : %d\n", reader->cursor);
	if (token && ft_strappend(&(reader->rest), token->value))
		return (-1);
	if (token && (ret = append_token(tokens, token, reader->state, reader)))
		return (ret);
	printf("rest : |%s|\n", reader->rest);
	return (0);
}

int			manage_last_token(t_reader *reader, t_token **tokens)
{
	t_token *token;
	int		ret;
	
	token = *tokens;
	while (token->next)
		token = token->next;
	printf("reader state : %d\n", reader->state);
	if (g_automate[token->lexem][0] == -2 || g_automate[token->lexem][0] == -3)
		return (0);
	printf("token state : %d\n", token->lexem);
	reader->cursor = 0;
	reader->state = automate('\n', reader->state);
	if ((ret = complete_token(token, reader->state, reader)))
		return (ret);
	if (g_automate[reader->state][0] != -2 && g_automate[reader->state][0] != -3)
	{
		token->value = NULL;
		print_lex_error(reader->line, reader->col);
	}
	return (0);
}	

int			scanner_asm(int fd, t_token **tokens)
{
	t_reader	reader;
	int			ret;

	reader.line = 1;
	reader.col = 1;
	reader.state = 0;
	reader.rest = NULL;
	while ((reader.nb_chars = read(fd, reader.buff, BUFF_SIZE_ASM)))
	{
		printf("in the loop\n");
		if (reader.nb_chars == -1)
			return (-1);
		reader.cursor = 0;
		if ((ret = buff_manager(&reader, tokens)))
		{
			if (ret == -1)
				print_system_error(errno);
			ft_strdel(&(reader.rest));
			return (ret);
		}
		printf("after buff_manager\n");
	}
	if ((ret = manage_last_token(&reader, tokens)))
	{
		ft_strdel(&(reader.rest));
		return (ret);
	}
	ft_strdel(&(reader.rest));
	printf("end of loop\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:56:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/07 18:59:12 by ccepre           ###   ########.fr       */
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
	while (++i < 12)
	{
		if ((ret = ft_strchr(g_index_col_lex[i], c)))
			break ;
	}
	new_state = g_automate_lex[state][i];
	return (new_state);
}

static int	token_manager(t_token **token, t_token **tokens, t_reader *reader,\
		t_token **labels)
{
	t_token *new;

	append_token(tokens, *token);
	if (*token && (*token)->lexem == LABEL)
	{
//		print_token(*token);
		if (!(new = copy_token(*token)))
			return (1);
		append_token(labels, new);
	}
	*token = NULL;
	if (!(*token = create_token(&(reader->buff[reader->cursor + 1]), reader, 1)))
			return (1);
	return (0);
}

static int		state_manager_scan(t_token **tokens, t_token **token,\
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

int			manage_last_token(t_reader *reader, t_token **tokens)
{
	t_token *token;
	int		ret;
	
//	printf("manage last\n");
//	printf("state : %d\n", reader->state);
//	check_tokens(*tokens);
	if (!(token = get_back_token(tokens)))
		return (0);
//	printf("token : %p\n", token);
	if (g_automate_lex[token->lexem][0] == -2\
			|| g_automate_lex[token->lexem][0] == -3)
	{
//		printf("last was ok\n");
		return (0);
	}
	if (reader->state != 0)
		reader->state = automate('\n', reader->state);
	if (g_automate_lex[reader->state][0] != -2\
			&& g_automate_lex[reader->state][0] != -3)
	{
//		printf("not final state\n");
		token->value = NULL;
		free_token(&token);
		return (reader->state == 0 ? 0\
				: print_lex_error(reader->line, reader->col));
	}
//	reader->cursor = 0;
	if ((ret = complete_token(token, reader->state, reader)))
	{		
//		printf("issue complete\n");
		token->value = NULL;
		free_token(&token);
		return (ret);
	}
	append_token(tokens, token);
//	printf("\n\nend manage :\n");
//	check_tokens(*tokens);
	return (0);
}

int				manage_end_buffer(t_reader *reader, t_token **tokens, t_token *token)
{
	int ret;


	if (g_automate_lex[reader->state][0] != -2\
			&& g_automate_lex[reader->state][0] != -3)
	{
		if (ft_strnappend(&(reader->rest), token->value,\
					reader->buff + reader->cursor - token->value)) // + 1 ???
			return (-1); 
		token->value = reader->buff;
	}
	else
		if ((ret = complete_token(token, reader->state, reader)))
			return (ret);
	append_token(tokens, token);
	return (0);
}

static int		buff_manager(t_reader *reader, t_token **tokens, t_token **labels)
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
			if (ret == -1)
				print_sys_error(errno);
			ft_strdel(&(reader.rest));
			return (ret);
		}
	}
	if ((ret = manage_last_token(&reader, tokens)))
	{
		ft_strdel(&(reader.rest));
		return (ret);
	}
	ft_strdel(&(reader.rest));
	return (0);
}

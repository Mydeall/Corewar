/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:08:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/03 18:13:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// ATTENTION : DIR/IND laber garde ':' au dbt
// VERIF REG
// VERIF len name comment

static int	verif_command(t_token *token)
{
	int ret;
	int ret2;

	ret2 = 0;
	if ((ret = strncmpchr(token->value, "name", 4)) == -1)
	{
		if (!ft_strchr(" \t", token->value[4]))
			return (print_lex_error(token->line, token->col + 5));
		token->lexem = NAME;
	}
	else if ((ret2 = strncmpchr(token->value, "comment", 7)) != -1)
	{
		ret = ret > ret2 ? ret : ret2;
		return (print_lex_error(token->line, token->col + ret));
	}
	if (token->lexem == COMMENT && !ft_strchr(" \t", token->value[7]))
		return (print_lex_error(token->line, token->col + 8));
	while (*(token->value) != '\"')
		(token->value)++;
	(token->value)++;
	return (0);
}
	
static int	verif_opcode(t_token *token, int len)
{
	int i;
	int	ret_max;

	i = -1;
	ret_max = 0;
	while (++i < 16)
	{
		if (!ft_strncmp(token->value, g_op_tab[i].inst, len))
		{
			if (!(token->value = ft_itoa(i + 1)))
				return (-1);
			return (0);
		}
	}
	return (print_lex_error(token->line, token->col + len));
}

static int		trim_front_chars(t_token *token, t_reader *reader, int *len)
{
	while (*(token->value) == '\t' || *(token->value) == ' '
			|| *(token->value) == '%' || *(token->value) == '.')
	{
		if (*(token->value) == '\t')
			token->col += 4;
		if (*(token->value) == ' ')
			token->col++;
		(token->value)++;
	}
	if (token->lexem == REGISTER)
		(token->value)++;
	if (token->lexem == COMMENT)
	{
		if (verif_command(token))
		{
			ft_strdel(&(reader->rest));
			return (1);
		}
	}
	*len = reader->rest ? ft_strlen(token->value)\
		  : reader->buff + reader->cursor - token->value + 1;
	if (token->value[*len - 1] == ':' || token->value[*len - 1] == '\"')
		(*len)--;
	return (0);
}

int	create_value(t_token *token, t_reader *reader)
{
	int		len;
	int		ret;
	
	if (reader->rest)
	{
		if (reader->cursor >= 0)
			if (ft_strnappend(&(reader->rest), reader->buff, reader->cursor))
				return (-1);
		token->value = reader->rest;
	}
	if (trim_front_chars(token, reader, &len))
		return (1);
	if (token->lexem == OPCODE)
	{
		ret = verif_opcode(token, len);
		ft_strdel(&(reader->rest));
		return (ret);
	}
	if (!(token->value = ft_strsub(token->value, 0, len)))
		return (-1);
	if (reader->rest)
		ft_strdel(&(reader->rest));
	return (0);
}

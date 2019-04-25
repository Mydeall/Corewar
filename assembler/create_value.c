/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:08:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/25 18:21:31 by ccepre           ###   ########.fr       */
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
		token->lexem = NAME;
	else if ((ret2 = strncmpchr(token->value, "comment", 7)) != -1)
	{
		printf("ret = %d -- ret2 = %d\n", ret, ret2);
		ret = ret > ret2 ? ret : ret2;
		return (print_lex_error(token->line, token->col + ret));
	}
	while (*(token->value) != '\"')
		(token->value)++;
	(token->value)++;
	return (0);
}
	
static int	verif_opcode(t_token *token, int len)
{
	int i;

	i = -1;
	printf("token : %p\n", token);
	if (token)
		printf("value : |%s|\n", token->value);
	while (++i < 16)
	{
		if (!ft_strncmp(g_instructions[i], token->value, len))
		{
			if (!(token->value = ft_itoa(i + 1)))
				return (-1);
			return (0);
		}
	}
	return (print_lex_error(token->line, token->col));
}

int	create_value(t_token *token, t_reader *reader)
{
	int		len;
	int		ret;
	
	if (reader->rest)
	{
		printf("cursor : %d\n", reader->cursor);
		if (reader->cursor >= 0)
			if (ft_strnappend(&(reader->rest), reader->buff, reader->cursor))
				return (-1);
		token->value = reader->rest;
	}
	printf("create_value\n");
	while (*(token->value) == '\t' || *(token->value) == ' '
			|| *(token->value) == '%' || *(token->value) == '.')
	{
		(token->value)++;
		if (*(token->value) == '\t' || *(token->value) == ' ')
			(token->col)++;
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
	len = reader->rest ? ft_strlen(token->value)\
		  : reader->buff + reader->cursor - token->value + 1;
	printf("len : %d\n", len);
	if (token->lexem == OPCODE)
	{
		ret = verif_opcode(token, len);
		ft_strdel(&(reader->rest));
		return (ret);
	}
	if (token->value[len - 1] == ':' || token->value[len - 1] == '\"')
		len--;
	if (!(token->value = ft_strsub(token->value, 0, len)))
		return (-1);
	printf("value : |%s|\n", token->value);
	if (reader->rest)
		ft_strdel(&(reader->rest));
	return (0);
}

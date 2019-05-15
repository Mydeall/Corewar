/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:38:04 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 17:54:15 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_lex_error(int line, int col)
{
	ft_printf("%d:%d: Lexical error\n", line, col);
	return (1);
}

int		print_sys_error(int errnum)
{
	char *error;

	error = strerror(errnum);
	ft_printf("System error: %s\n", error);
	ft_strdel(&error);
	return (-1);
}

int		print_dup_label_error(t_token *token, t_token *dup)
{
	ft_printf("%d:%d: Syntax error: Duplicate label\n",\
			dup->line, dup->col);
	ft_printf("First definition: line: %d, col: %d\n",\
			token->line, token->col);
	return (1);
}

int		print_label_error(t_token *token)
{
	ft_printf("%d:%d: Syntax error: Undeclared label\n",\
			token->line, token->col);
	return (1);
}

int		print_syn_error(int line, int col, t_lex lexem, int state)
{
	int	i;
	int	j;
	int ret;

	i = -1;
	j = 0;
	ft_printf("%d:%d: Syntax error\nGiven expression: ",
			line, col);
	print_lexem(lexem);
	ft_printf("\nExpected expression(s): ");
	while (++i < 9)
	{
		ret = g_automate_syn[state][i];
		if (ret != -1)
		{
			if (j)
				ft_printf(", ");
			print_lexem(g_index_col_syn[i]);
			j++;
		}
	}
	ft_printf("\n");
	return (1);
}

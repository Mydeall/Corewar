/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:46:55 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/29 20:09:52 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_lex_error(int line, int col)
{
	printf("lexical error : line %d, col %d\n", line, col);
	return (1);
}

int		print_arg_error(int	error_id)
{
	if (error_id == 1)
		write(1, "usage\n", 6);
	return (1);
}

int		print_system_error(int errnum)
{
	printf("System error : %s\n", strerror(errnum));
	return (-1);
}

int		print_syn_error(t_token *token, int state)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	print_token(token);
	printf("syn error line %d, col %d : expected expression(s) : ",
			token->line, token->col);
	while (++i < 9)
	{
		if (g_automate_syn[state][i] != -1)
		{
			if (j)
				printf(", "); 
			print_lexem(g_index_col_syn[i]);
			j++;
		}
	}
	printf("\n");
	return (1);
}

int		print_len_error(t_token *token)
{
	(void)token;
	return (1);
}

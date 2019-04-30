/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:46:55 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/30 15:23:14 by ccepre           ###   ########.fr       */
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

int		print_label_error(t_token *token, t_token *dup)
{
	printf("Syn error : duplicate label line : %d, col : %d\n",\
			dup->line, dup->col);
	printf("First definition line : %d, col : %d\n", token->line, token->col);
	return (1);
}

int		print_syn_error(t_token *token, int state)
{
	int	i;
	int	j;
	int ret;

	i = -1;
	j = 0;
	printf("Syn error line %d, col %d :\nGiven expression : ",
			token->line, token->col);
	print_lexem(token->lexem);
	printf("\nExpected expression(s) : ");
	while (++i < 9)
	{
		ret = g_automate_syn[state][i];
		if (ret != -1)
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

int		print_len_error(t_token *token, int max)
{
	printf("Syn error line %d, col %d : invalid size (max size is %d)\n",\
			token->line, token->col, max);
	return (1);
}

int		print_int_error(t_token *token, int min, int max)
{
	printf("Syn error line %d, col %d : invalid value (min = %d | max =  %d)\n",\
			token->line, token->col, min, max);
	return (1);
}

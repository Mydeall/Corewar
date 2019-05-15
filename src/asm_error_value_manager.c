/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error_value_manager.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:38:25 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/10 14:17:59 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_arg_error(int errnum, char *prog_name)
{
	if (errnum == 1)
		ft_printf("Usage: %s <sourcefile.s>\n", prog_name);
	else
		ft_printf("Invalid file name: must be <file_name>.s\n");
	return (1);
}

int		print_len_error(t_token *token, int max)
{
	ft_printf("%d:%d: Syntax error: Invalid size (max size is %d)\n",\
			token->line, token->col, max);
	return (1);
}

int		print_int_error(t_token *token, int min, int max)
{
	ft_printf("%d:%d: Syntax error: ", token->line, token->col);
	ft_printf("Invalid register value (min: %d & max: %d)\n", min, max);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_value_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:20:06 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/08 18:08:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_arg_error(int errnum, char *prog_name)
{
	if (errnum == 1)
		ft_printf("Usage: %s <sourcefile.s>\n", prog_name);
	else
		ft_printf("Invalid file name : must be <file_name>.s\n");
	return (1);
}

int		print_len_error(t_token *token, int max)
{
	ft_printf("Syn error line %d, col %d : invalid size (max size is %d)\n",\
			token->line, token->col, max);
	return (1);
}

int		print_int_error(t_token *token, int min, int max)
{
	ft_printf("Syn error line %d, col %d : ", token->line, token->col);
	ft_printf("invalid value (min = %d | max =  %d)\n", min, max);
	return (1);
}

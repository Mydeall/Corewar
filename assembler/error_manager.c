/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:46:55 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/25 12:18:51 by ccepre           ###   ########.fr       */
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


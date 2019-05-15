/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:13 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 16:42:03 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void	ft_error_read(t_vm *vm, char *str)
{
	ft_printf("Can't read source file %s\n", str);
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-1);
}

void	ft_error_too_many(t_vm *vm)
{
	ft_printf("Too many champions\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-1);
}

void	ft_incorrect_number(t_vm *vm)
{
	ft_printf("The provided number is incorrect");
	ft_printf(", please provide a positive integer.\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-1);
}

void	ft_error_already_assigned(t_vm *vm)
{
	ft_printf("Two champions can't have the same number");
	ft_printf(", please provide another positive integer.\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-1);
}

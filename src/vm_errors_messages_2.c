/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors_messages_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:13 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 16:42:19 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void	error_wrong_header(t_vm *vm)
{
	ft_printf("Error: File has an invalid header\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-2);
}

void	error_wrong_weight(t_vm *vm)
{
	ft_printf("Error: File has a code size");
	ft_printf(" that differs from what its header says\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-2);
}

void	error_champ_too_big(t_vm *vm)
{
	ft_printf("Error: Champion is too big\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-2);
}

void	error_champ_too_small(t_vm *vm)
{
	ft_printf("Error: File test is too small to be a champion\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-2);
}

void	error_read(t_vm *vm)
{
	ft_printf("Error: reading champion code\n");
	free_structs(vm);
	ft_memdel((void **)&vm);
	exit(-2);
}

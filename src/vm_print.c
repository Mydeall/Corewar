/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:22:40 by malluin           #+#    #+#             */
/*   Updated: 2019/04/17 19:26:13 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libftprintf.h"

void	print_intro(t_vm *vm)
{
	short	i;

	i = 0;
	if (vm->players[0] != NULL && vm->nb_players > 0)
	{
		ft_printf("Introducing contestants...\n");
		while (i < vm->nb_players && vm->players[i] != NULL)
		{
			ft_printf("* Player %d, weighing %3d bytes, \"%s\", (\"%s\")\n",
			vm->players[i]->player_number, vm->players[i]->header->prog_size,
			vm->players[i]->header->prog_name, vm->players[i]->header->comment);
			i++;
		}
	}
}

void	dump_memory(t_vm *vm)
{
	int i = 0;

	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02hhx ", vm->arena[i++].by);
		if (i % 64 == 0)
			ft_printf("\n");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:22:40 by malluin           #+#    #+#             */
/*   Updated: 2019/05/14 16:39:38 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	ft_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N -v N | -g] [[-n N] <champion1.cor>]");
	ft_printf(" <...>\n");
	ft_printf("#### TEXT OUTPUT MODE #######################\n");
	ft_printf("-dump N: Dumps memory after N cycles then exits\n");
	ft_printf("-v    N: Verbosity levels, can be added ");
	ft_printf("together to enable several:\n");
	ft_printf("	- 0 : Show only essentials\n");
	ft_printf("	- 1 : Show lives\n");
	ft_printf("	- 2 : Show cycles\n");
	ft_printf("	- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("	- 8 : Show deaths\n");
	ft_printf("	- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("	- 32 : Show Cycles_to_die changes\n");
	ft_printf("#### NCURSES OUTPUT MODE #######################\n");
	ft_printf("-g    : Ncurses output mode\n");
	exit(-1);
}

void	print_intro(t_vm *vm)
{
	short	i;

	i = 0;
	if (vm->players[0] != NULL && vm->nb_players > 0)
	{
		ft_printf("Introducing contestants...\n");
		while (i < vm->nb_players && vm->players[i] != NULL)
		{
			ft_printf("* Player %d, weighing %d bytes, \"",
			ft_iabs(vm->players[i]->player_number),
			vm->players[i]->header->prog_size);
			write(1, &vm->players[i]->header->prog_name,
				ft_strlen(vm->players[i]->header->prog_name));
			write(1, "\" (\"", 4);
			write(1, &vm->players[i]->header->comment,
				ft_strlen(vm->players[i]->header->comment));
			write(1, "\") !\n", 5);
			i++;
		}
	}
}

void	dump_memory(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02hhx ", vm->arena[i++].by);
		if (i % 32 == 0)
			ft_printf("\n");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:12:29 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 17:07:23 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft.h"
#include "vm.h"

void	ft_print_xstr(int size, char *str, int wid)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (i % wid == 0)
			ft_printf("\n");
		ft_printf("%02hhx ", str[i++]);
	}
	ft_printf("\n");
}

void	ft_print_xarena(t_vm *vm, int wid)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % wid == 0)
			ft_printf("\n");
		ft_printf("%02hhx ", vm->arena[i++].by);
	}
	ft_printf("\n");
}

void	ft_print_process(t_vm *vm)
{
	int			i;
	int			j;
	t_process	*process;

	i = 0;
	process = vm->process;
	if (vm->debug == 0)
		return ;
	while (process != NULL)
	{
		j = 0;
		ft_printf("\nProcess %2d  | ", i);
		ft_printf("PC %d  | ", process->pc);
		ft_printf("carry %d\n", process->carry);
		while (j < REG_NUMBER)
		{
			ft_printf("reg %2d: %3d | reg %2d: %3d\n", j,
			read_reg(process->regs[j]), j + 1, read_reg(process->regs[j + 1]));
			j += 2;
		}
		i++;
		process = process->next;
	}
}

void	ft_print_players(t_vm *vm)
{
	int		i;

	i = 0;
	if (vm->debug == 0)
		return ;
	while (i < vm->players_alive)
	{
		ft_printf("Player: %d\n", vm->players[i]->player_number);
		ft_printf("Order: %d\n", vm->players[i]->order_arg);
		ft_printf("File_path: %s\n", vm->players[i]->file_path);
		ft_printf("Magic: %07x\n", vm->players[i]->header->magic);
		ft_printf("prog_name: %s\n", vm->players[i]->header->prog_name);
		ft_printf("comment: %s\n", vm->players[i]->header->comment);
		ft_printf("\n");
		i++;
	}
	ft_print_process(vm);
	ft_printf("\n---------- ARENA ----------\n");
	ft_printf("%p\n", vm->arena);
	ft_printf("%s\n", vm->arena);
}

void	increment_memory(t_vm *vm)
{
	static int i = 0;

	vm->arena[i++].by++;
	if (i == MEM_SIZE)
		i = 0;
}

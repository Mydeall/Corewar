/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:39:31 by malluin           #+#    #+#             */
/*   Updated: 2019/04/22 15:36:35 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ncurses.h>

int		read_arena(t_vm *vm, int pos, int size)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	if (size > 4)
		size = 4;
	else if (size <= 0)
		return (0);
	while (i < size)
	{
		res += vm->arena[(pos + i) % 4096].by << (size - i - 1) * 8;
		i++;
	}
	return (res);
}

int		check_args(t_vm *vm, t_process *proc)
{
	(void)(vm);
	(void)(proc);
		return (1);
}

int		op_live(t_vm *vm, t_process *proc)
{
	int		i;
	int		nb;

	i = 0;
	proc->last_live = vm->cycles;
	vm->number_of_live += 1;
	nb = read_arena(vm, proc->pc + 1, DIR_SIZE);
	proc->step_over = 5;
	while (i < vm->nb_players)
	{
		if (vm->players[i] != NULL && nb == vm->players[i]->player_number)
		{
			vm->last_player_live = nb;
			break;
		}
		i++;
	}
	return (1);
}

int		op_add(t_vm *vm, t_process *proc)
{
	int		r1;
	int		r2;
	int		r3;

	r1 = read_arena(vm, proc->pc + 2, T_REG);
	r2 = read_arena(vm, proc->pc + 3, T_REG);
	r3 = read_arena(vm, proc->pc + 4, T_REG);
	r1 = read_reg(proc->regs[r1 - 1]);
	r2 = read_reg(proc->regs[r2 - 1]);
	r2 += r1;
	assign_reg(proc, r3, r2);
	proc->step_over = 5;
	proc->carry = r2 == 0 ? 1 : 0;
	ft_print_players(vm);
	return (1);
}

int		op_sub(t_vm *vm, t_process *proc)
{
	int		r1;
	int		r2;
	int		r3;

	r1 = read_arena(vm, proc->pc + 2, T_REG);
	r2 = read_arena(vm, proc->pc + 3, T_REG);
	r3 = read_arena(vm, proc->pc + 4, T_REG);
	r1 = read_reg(proc->regs[r1 - 1]);
	r2 = read_reg(proc->regs[r2 - 1]);
	r2 = r1 - r2;
	assign_reg(proc, r3, r2);
	proc->step_over = 5;
	proc->carry = r2 == 0 ? 1 : 0;
	ft_print_players(vm);
	return (1);
}

int		op_and(t_vm *vm, t_process *proc)
{
	int		r1;
	int		r2;
	int		r3;

	r1 = read_arena(vm, proc->pc + 2, T_REG);
	r2 = read_arena(vm, proc->pc + 3, T_REG);
	r3 = read_arena(vm, proc->pc + 4, T_REG);
	r1 = read_reg(proc->regs[r1 - 1]);
	r2 = read_reg(proc->regs[r2 - 1]);
	r2 = r2 & r1;
	assign_reg(proc, r3, r2);
	proc->step_over = 5;
	proc->carry = r2 == 0 ? 1 : 0;
	ft_print_players(vm);
	return (1);
}

int		op_or(t_vm *vm, t_process *proc)
{
	int		r1;
	int		r2;
	int		r3;

	r1 = read_arena(vm, proc->pc + 2, T_REG);
	r2 = read_arena(vm, proc->pc + 3, T_REG);
	r3 = read_arena(vm, proc->pc + 4, T_REG);
	r1 = read_reg(proc->regs[r1 - 1]);
	r2 = read_reg(proc->regs[r2 - 1]);
	r2 = r2 | r1;
	assign_reg(proc, r3, r2);
	proc->step_over = 5;
	proc->carry = r2 == 0 ? 1 : 0;
	ft_print_players(vm);
	return (1);
}

int		op_xor(t_vm *vm, t_process *proc)
{
	int		r1;
	int		r2;
	int		r3;

	r1 = read_arena(vm, proc->pc + 2, T_REG);
	r2 = read_arena(vm, proc->pc + 3, T_REG);
	r3 = read_arena(vm, proc->pc + 4, T_REG);
	r1 = read_reg(proc->regs[r1 - 1]);
	r2 = read_reg(proc->regs[r2 - 1]);
	r2 = r2 ^ r1;
	assign_reg(proc, r3, r2);
	proc->step_over = 5;
	proc->carry = r2 == 0 ? 1 : 0;
	ft_print_players(vm);
	return (1);
}

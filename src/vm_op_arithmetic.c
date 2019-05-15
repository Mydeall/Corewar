/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_arithmetic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:39:31 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 18:30:11 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include <ncurses.h>

int		op_add(t_vm *vm, t_process *proc)
{
	int		r1;
	int		r2;
	int		r3;

	r1 = read_arena(vm, proc->pc + 2, T_REG);
	r2 = read_arena(vm, proc->pc + 3, T_REG);
	r3 = read_arena(vm, proc->pc + 4, T_REG);
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d r%d r%d\n", r1, r2, r3);
	proc->step_over = 5;
	if ((r1 < 1 || r1 > REG_NUMBER) || (r2 < 1 || r2 > REG_NUMBER))
		return (1);
	r1 = read_reg(proc->regs[r1 - 1]);
	r2 = read_reg(proc->regs[r2 - 1]);
	r2 += r1;
	assign_reg(proc, r3, r2);
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
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d r%d r%d\n", r1, r2, r3);
	proc->step_over = 5;
	if ((r1 < 1 || r1 > REG_NUMBER) || (r2 < 1 || r2 > REG_NUMBER))
		return (1);
	r1 = read_reg(proc->regs[r1 - 1]);
	r2 = read_reg(proc->regs[r2 - 1]);
	r2 = r1 - r2;
	assign_reg(proc, r3, r2);
	proc->carry = r2 == 0 ? 1 : 0;
	ft_print_players(vm);
	return (1);
}

int		*read_args(t_vm *vm, t_process *proc, int *size, int nb_args)
{
	int		*r;
	int		i;

	i = 0;
	if (!(r = (int *)malloc(sizeof(int) * nb_args)))
		return (NULL);
	while (i < nb_args)
	{
		if (vm->enc_byte[i] == T_REG)
		{
			r[i] = read_arena(vm, proc->pc + *size, T_REG);
			if (r[i] >= 1 && r[i] <= REG_NUMBER && i != 2)
				r[i] = read_reg(proc->regs[r[i] - 1]);
		}
		else if (vm->enc_byte[i] == DIR_SIZE)
			r[i] = read_arena(vm, proc->pc + *size, DIR_SIZE);
		else if (vm->enc_byte[i] == IND_SIZE)
		{
			r[i] = read_arena(vm, proc->pc + *size, IND_SIZE);
			r[i] = read_arena(vm, proc->pc + r[i] % IDX_MOD, DIR_SIZE);
		}
		*size += vm->enc_byte[i++];
	}
	return (r);
}

int		op_or(t_vm *vm, t_process *proc)
{
	int		size;
	int		*r;

	r = NULL;
	size = 2;
	ft_decode_byte2(vm, vm->arena[(proc->pc + 1 + MEM_SIZE) % MEM_SIZE].by);
	if (!(r = read_args(vm, proc, &size, 3)))
		return (0);
	if ((vm->detail & 4) != 0)
		ft_printf(" %d %d r%d\n", r[0], r[1], r[2]);
	proc->step_over = size;
	r[1] = r[0] | r[1];
	if (r[2] >= 1 && r[2] <= REG_NUMBER)
		assign_reg(proc, r[2], r[1]);
	proc->carry = r[1] == 0 ? 1 : 0;
	ft_memdel((void **)&r);
	ft_print_players(vm);
	return (1);
}

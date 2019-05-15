/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_load_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:04:46 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/13 15:53:30 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

int		op_load_utils(t_vm *vm, t_process *p, int r, int idx_m)
{
	int		res;

	res = 0;
	if (vm->enc_byte[0] == DIR_SIZE)
	{
		res = read_arena(vm, (p->pc + 2), DIR_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", res);
		assign_reg(p, r, res);
	}
	else if (vm->enc_byte[0] == IND_SIZE)
	{
		res = read_arena(vm, (p->pc + 2), IND_SIZE);
		if (idx_m == 1)
			res = read_arena(vm, p->pc + res % IDX_MOD, DIR_SIZE);
		else
			res = read_arena(vm, p->pc + res, DIR_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", res);
		assign_reg(p, r, res);
	}
	return (res);
}

int		op_ldi_utils(t_vm *vm, t_process *p, int k, int size)
{
	int res;

	res = 0;
	if (vm->enc_byte[k] == 1)
	{
		res = read_arena(vm, p->pc + size, 1);
		if ((vm->detail & 4) != 0)
			ft_printf(" r%d", res);
		res = read_reg(p->regs[res - 1]);
	}
	else if (vm->enc_byte[k] == 2)
	{
		res = read_arena(vm, p->pc + size, IND_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", read_arena(vm, p->pc + res, DIR_SIZE));
		res = read_arena(vm, p->pc + res % IDX_MOD, DIR_SIZE);
	}
	else if (vm->enc_byte[k] == 4)
	{
		vm->enc_byte[k] = 2;
		res = read_arena(vm, p->pc + size, IND_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", read_arena(vm, p->pc + size, IND_SIZE));
	}
	return (res);
}

int		op_lldi_utils(t_vm *vm, t_process *p, int k, int size)
{
	int res;

	res = 0;
	if (vm->enc_byte[k] == 1)
	{
		res = read_arena(vm, p->pc + size, 1);
		if ((vm->detail & 4) != 0)
			ft_printf(" r%d", res);
		res = read_reg(p->regs[res - 1]);
	}
	else if (vm->enc_byte[k] == 2)
	{
		res = read_arena(vm, p->pc + size, IND_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", read_arena(vm, p->pc + res, DIR_SIZE));
		res = read_arena(vm, p->pc + res, DIR_SIZE);
	}
	else if (vm->enc_byte[k] == 4)
	{
		vm->enc_byte[k] = 2;
		res = read_arena(vm, p->pc + size, IND_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", read_arena(vm, p->pc + size, IND_SIZE));
	}
	return (res);
}

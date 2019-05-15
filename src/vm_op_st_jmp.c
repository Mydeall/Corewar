/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_st_jmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:19:58 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/13 16:03:14 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

int		op_zjmp(t_vm *vm, t_process *p)
{
	int		jump;

	jump = 0;
	jump = read_arena(vm, p->pc + 1, IND_SIZE);
	if (p->carry == 0)
	{
		p->step_over = 3;
		if ((vm->detail & 4) != 0)
			ft_printf(" %d FAILED\n", jump);
		return (1);
	}
	p->step_over = jump % IDX_MOD;
	if ((vm->detail & 4) != 0)
		ft_printf(" %d OK\n", p->step_over);
	return (2);
}

void	dirty(t_vm *vm, t_process *p, int position)
{
	if ((vm->detail & 4) != 0)
		ft_printf(" %d\n", position);
	reg_to_mem(vm, p, vm->arena[verif(p->pc + 2)].by,
		(p->pc + position % IDX_MOD + MEM_SIZE) % MEM_SIZE);
}

int		op_store(t_vm *vm, t_process *p)
{
	int				position;

	ft_decode_byte2(vm, vm->arena[verif(p->pc + 1)].by);
	if (is_register(vm->enc_byte[0], vm->arena[verif(p->pc + 2)].by) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d", vm->arena[verif(p->pc + 2)].by);
	if (is_register(vm->enc_byte[1], vm->arena[verif(p->pc + 2
			+ vm->enc_byte[0])].by))
	{
		reg_to_reg(vm->arena[verif(p->pc + 2)].by,
			vm->arena[verif(p->pc + 3)].by, p);
		if ((vm->detail & 4) != 0)
			ft_printf(" r%d\n", vm->arena[verif(p->pc + 3)].by);
	}
	else
	{
		position = read_arena(vm, p->pc + 2 + vm->enc_byte[0], IND_SIZE);
		dirty(vm, p, position);
	}
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	return (1);
}

int		op_sti_utils(t_vm *vm, t_process *p, int k, int size)
{
	int		res;

	res = 0;
	if (vm->enc_byte[k] == 1)
	{
		res = read_arena(vm, p->pc + size, T_REG);
		if ((vm->detail & 4) != 0 && res > 0 && res <= REG_NUMBER)
			ft_printf(" %d", read_reg(p->regs[res - 1]));
		res = (res > 0 && res <= REG_NUMBER) ? read_reg(p->regs[res - 1]) : res;
	}
	else if (vm->enc_byte[k] == 2)
	{
		res = read_arena(vm, p->pc + size, IND_SIZE);
		res = read_arena(vm, p->pc + res % IDX_MOD, REG_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", read_arena(vm, p->pc + res, REG_SIZE));
	}
	else if (vm->enc_byte[k] == 4)
	{
		vm->enc_byte[k] = 2;
		res = res + read_arena(vm, p->pc + size, IND_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf(" %d", read_arena(vm, p->pc + size, IND_SIZE));
	}
	return (res);
}

int		op_sti(t_vm *vm, t_process *p)
{
	int				k;
	int				res;
	int				size;

	ft_decode_byte2(vm, vm->arena[(p->pc + 1 + MEM_SIZE) % MEM_SIZE].by);
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d", vm->arena[(p->pc + 1 + vm->enc_byte[0] + MEM_SIZE)
			% MEM_SIZE].by);
	res = 0;
	size = 3;
	k = 1;
	while (k < 3)
	{
		res = res + op_sti_utils(vm, p, k, size);
		size = size + vm->enc_byte[k];
		k++;
	}
	reg_to_mem(vm, p, vm->arena[((p->pc + 2) + MEM_SIZE) % MEM_SIZE].by,
		p->pc + res % IDX_MOD);
	if ((vm->detail & 4) != 0)
		ft_printf("\n	-> store to %d (with pc and mod %d)\n", res,
			p->pc + res % IDX_MOD);
	p->step_over = vm->enc_byte[0] + vm->enc_byte[1] + vm->enc_byte[2] + 2;
	return (1);
}

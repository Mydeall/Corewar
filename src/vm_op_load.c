/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:19:58 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/14 16:23:39 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

int		op_load(t_vm *vm, t_process *p)
{
	int				res;
	int				r;

	ft_decode_byte2(vm, vm->arena[(p->pc + 1 + MEM_SIZE) % MEM_SIZE].by);
	r = read_arena(vm, p->pc + 2 + vm->enc_byte[0], vm->enc_byte[1]);
	if (is_register(vm->enc_byte[1], r) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	res = op_load_utils(vm, p, r, 1);
	p->carry = res == 0 ? 1 : 0;
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d\n", r);
	return (1);
}

int		op_lld(t_vm *vm, t_process *p)
{
	int				res;
	int				r;

	ft_decode_byte2(vm, vm->arena[(p->pc + 1 + MEM_SIZE) % MEM_SIZE].by);
	r = read_arena(vm, p->pc + 2 + vm->enc_byte[0], vm->enc_byte[1]);
	if (is_register(vm->enc_byte[1], r) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	res = op_load_utils(vm, p, r, 0);
	p->carry = res == 0 ? 1 : 0;
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d\n", r);
	return (1);
}

int		op_ldi(t_vm *vm, t_process *p)
{
	int				res;
	int				reg;
	int				size;
	int				k;

	k = 0;
	res = 0;
	reg = 0;
	size = 2;
	ft_decode_byte2(vm, vm->arena[(p->pc + 1 + MEM_SIZE) % MEM_SIZE].by);
	while (k < 2)
	{
		res = res + op_ldi_utils(vm, p, k, size);
		size = size + vm->enc_byte[k];
		k++;
	}
	reg = read_arena(vm, p->pc + size++, T_REG);
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d\n	| -> load from %d (with pc and mod %d)\n", reg,
			res, (p->pc + (res % IDX_MOD)) % MEM_SIZE);
	assign_reg(p, reg, read_arena(vm, p->pc + (res % IDX_MOD), REG_SIZE));
	p->step_over = size;
	return (1);
}

int		op_lldi(t_vm *vm, t_process *p)
{
	int				res;
	int				reg;
	int				size;
	int				k;

	k = 0;
	res = 0;
	reg = 0;
	size = 2;
	ft_decode_byte2(vm, vm->arena[(p->pc + 1 + MEM_SIZE) % MEM_SIZE].by);
	while (k < 2)
	{
		res = res + op_lldi_utils(vm, p, k, size);
		size = size + vm->enc_byte[k];
		k++;
	}
	reg = read_arena(vm, p->pc + size++, T_REG);
	if ((vm->detail & 4) != 0)
		ft_printf(" r%d\n	| -> load from %d (with pc and mod %d)\n", reg,
			res, (p->pc + (res)) % MEM_SIZE);
	assign_reg(p, reg, read_arena(vm, p->pc + (res), REG_SIZE));
	p->step_over = size;
	p->carry = read_arena(vm, p->pc + (res), REG_SIZE) == 0 ? 1 : 0;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_arithmetic_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:32:55 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/09 18:29:48 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include <ncurses.h>

int		op_xor(t_vm *vm, t_process *proc)
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
	r[1] = r[0] ^ r[1];
	if (r[2] >= 1 && r[2] <= REG_NUMBER)
		assign_reg(proc, r[2], r[1]);
	proc->carry = r[1] == 0 ? 1 : 0;
	ft_memdel((void **)&r);
	ft_print_players(vm);
	return (1);
}

int		op_and(t_vm *vm, t_process *proc)
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
	r[1] = r[0] & r[1];
	if (r[2] >= 1 && r[2] <= REG_NUMBER)
		assign_reg(proc, r[2], r[1]);
	proc->carry = r[1] == 0 ? 1 : 0;
	ft_memdel((void **)&r);
	ft_print_players(vm);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:10:50 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/09 18:53:30 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

void	reg_to_reg(int src_reg, int dst_reg, t_process *p)
{
	int		count;

	count = 0;
	if (dst_reg > REG_NUMBER || dst_reg < 1 || p == NULL)
		return ;
	while (count < REG_SIZE)
	{
		p->regs[dst_reg - 1][count] = p->regs[src_reg - 1][count];
		count++;
	}
}

void	reg_to_mem(t_vm *vm, t_process *p, int reg, int pos)
{
	int		count;
	int		i;

	count = 0;
	if (reg < 1 || reg > REG_NUMBER)
		return ;
	while (count < REG_SIZE)
	{
		i = ((pos + count) % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
		vm->arena[i].by = p->regs[reg - 1][count];
		vm->arena[i].id = p->id_parent;
		vm->arena[i].st_id = 40;
		count++;
	}
}

int		verif(int nb)
{
	return ((nb % MEM_SIZE + MEM_SIZE) % MEM_SIZE);
}

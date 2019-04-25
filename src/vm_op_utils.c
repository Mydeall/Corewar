/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:20:14 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/22 16:10:36 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libftprintf.h"

int		*ft_decode_byte(unsigned char c, int *tab, t_vm *vm)
{
	tab[0] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[1] = vm->enc[(c >> 6)];
	c = (c << 4);
	tab[2] = vm->enc[(c >> 6)];
	c = (c << 6);
	tab[3] = vm->enc[(c >> 6)];
	return (tab);
}

int		is_register(int decoded_by, unsigned char arena_by)
{

	if (decoded_by != 1 || arena_by > 16 || arena_by <= 0)
	{
		// ft_printf("into the byte: %d \n", decoded_by);
		// ft_printf("arena byte: %d \n", arena_by);
		return (0);
	}
	return (1);
}

void				reg_to_reg(int src_reg, int dst_reg, t_process *p)
{
	int				count;

	count = 0;
	while (count < REG_SIZE)
	{
		p->regs[dst_reg][count] = p->regs[src_reg][count];
		// ft_printf("reg[%d][%d] = %d\n", dst_reg, count, p->regs[src_reg][count]);
		count++;
	}
}

void				reg_to_mem(int reg, int pos, t_vm *vm, t_process *p)
{
	int				count;

	count = 0;
	// ft_print_xarena(vm, 60);
	while (count < REG_SIZE)
	{
		// ft_printf("%d\n", by[1]);
		vm->arena[pos + count].by = p->regs[reg][count];
		// vm->arena[pos + count].by = 7;
		count++;
	}
	// ft_print_xarena(vm, 60);
}

void				mem_to_reg(int reg, int pos, t_vm *vm, t_process *p)
{
	int				count;

	count = 0;
	while (count < REG_SIZE)
	{
		// ft_printf("%d\n", by[1]);
		// vm->arena[pos + count].by = p->regs[reg][count];
		vm->arena[pos + count].by = 7;
		count++;
	}
}

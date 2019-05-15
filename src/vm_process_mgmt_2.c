/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_mgmt_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:35:34 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/09 18:37:14 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void		add_child_process(t_vm *vm, t_process *parent, int child_pc)
{
	t_process	*tmp;

	tmp = new_process(parent->id_parent, child_pc);
	vm->nb_process += 1;
	if (tmp == NULL || vm->process == NULL)
		return ;
	tmp->next = vm->process;
	vm->process = tmp;
	tmp->carry = parent->carry;
	tmp->last_live = parent->last_live;
	tmp->id_parent = parent->id_parent;
	ft_memcpy((void *)tmp->regs, (void *)parent->regs, sizeof(parent->regs));
	vm->arena[tmp->pc % MEM_SIZE].proc_id = 1;
}

void		create_processes(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		add_first_process_front(vm, vm->players[i++], &vm->process);
	}
}

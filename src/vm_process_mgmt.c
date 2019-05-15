/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_mgmt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:42:41 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 18:35:59 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libft.h"

t_process	*new_process(int id_parent, int pc)
{
	t_process	*node;
	static long	id = 1;

	if (!(node = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	node->pc = pc;
	node->carry = 0;
	node->wait_cycles = 0;
	node->last_live = 0;
	node->step_over = 0;
	node->next_op = 0;
	node->id_parent = id_parent;
	node->next = NULL;
	node->id_proc = id++;
	ft_bzero(node->regs, REG_NUMBER * REG_SIZE);
	return (node);
}

void		add_first_process_front(t_vm *vm, t_player *player,
			t_process **blist)
{
	t_process		*tmp;
	static int		id_visu = 1;

	tmp = new_process(id_visu++, player->code_start);
	vm->nb_process += 1;
	if (tmp == NULL || blist == NULL)
		return ;
	tmp->next = *blist;
	*blist = tmp;
	player->nb_process = 1;
	assign_reg(tmp, 1, player->player_number);
}

void		remove_process(t_vm *vm, t_process *parent, t_process *node)
{
	if (parent == NULL)
		parent = vm->process;
	if (parent == node)
	{
		vm->process = parent->next;
		ft_memdel((void **)&parent);
		vm->nb_process--;
	}
	else
	{
		while (parent && parent->next != node)
			parent = parent->next;
		if (parent == NULL)
			return ;
		parent->next = node->next;
		ft_memdel((void **)&node);
		vm->nb_process--;
	}
}

void		remove_dead_process(t_vm *vm)
{
	t_process *proc;
	t_process *tmp;
	t_process *parent;

	proc = vm->process;
	parent = NULL;
	while (proc)
	{
		if (proc->last_live <= vm->cycles - vm->cycle_to_die)
		{
			vm->arena[proc->pc % MEM_SIZE].proc_id = 0;
			tmp = proc;
			if ((vm->detail & 8) != 0)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				proc->id_proc, vm->cycles - proc->last_live - 1,
				vm->cycle_to_die);
			proc = proc->next;
			remove_process(vm, parent, tmp);
			continue;
		}
		else
			parent = proc;
		proc = proc->next;
	}
}

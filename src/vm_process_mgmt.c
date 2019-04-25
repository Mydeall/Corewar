/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_mgmt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:42:41 by malluin           #+#    #+#             */
/*   Updated: 2019/04/22 14:17:52 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"

t_process	*new_process(int id_parent, int pc)
{
	t_process	*node;

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
	ft_bzero(node->regs, REG_NUMBER * REG_SIZE);
	return (node);
}

void	add_first_process_front(t_vm *vm, t_player *player, t_process **blist)
{
	t_process	*tmp;

	tmp = new_process(player->player_number, player->code_start);
	vm->nb_process += 1;
	if (tmp == NULL || blist == NULL)
		return ;
	tmp->next = *blist;
	*blist = tmp;
	player->nb_process = 1;
	assign_reg(tmp, 1, player->player_number);
}

void	remove_process(t_vm *vm, t_process *node)
{
	t_process	*parent;

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

void	remove_dead_process(t_vm *vm)
{
	t_process *proc;
	t_process *tmp;

	proc = vm->process;
	while (proc)
	{
		if (proc->last_live <= vm->cycles - vm->cycle_to_die)
		{
			vm->arena[proc->pc].proc_id = 0;
			tmp = proc;
			proc = proc->next;
			remove_process(vm, tmp);
			continue;
		}
		proc = proc->next;
	}
}

// void	add_child_process(t_player *player, t_process *parent)
// {
// 	if (!(player->process = (t_process **)realloc(player->process,
// 		sizeof(t_process *) * (player->nb_process + 1))))
// 		return ;
// 	if (!(player->process[player->nb_process] = (t_process *)realloc(player->process,
// 		sizeof(t_process))))
// 		return ;
// 	player->nb_process++;
// 	ft_memcpy((void *)player->process[player->nb_process - 1], (void *)parent,
// 		sizeof(parent));
//
// }

void	create_processes(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		add_first_process_front(vm, vm->players[i++], &vm->process);
	}
}

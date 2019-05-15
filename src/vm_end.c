/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:29:54 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 16:42:47 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

void	free_structs(t_vm *vm)
{
	int			i;
	t_process	*tmp;

	i = -1;
	while (++i < vm->players_alive)
	{
		if (vm->players[i] == NULL)
			continue;
		ft_memdel((void **)&(vm->players[i]->header));
		ft_memdel((void **)&(vm->players[i]->file_path));
		ft_memdel((void **)&(vm->players[i]));
	}
	while (vm->process)
	{
		tmp = vm->process;
		vm->process = vm->process->next;
		ft_memdel((void **)&tmp);
	}
}

char	*find_player_name(t_vm *vm, int nb)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->players[i]->player_number == nb)
			break ;
		i++;
	}
	if (i != vm->nb_players)
		return (vm->players[i]->header->prog_name);
	else
		return (NULL);
}

void	end_game(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n", vm->last_player_live,
		find_player_name(vm, vm->last_player_live));
	free_structs(vm);
	ft_memdel((void **)&vm);
}

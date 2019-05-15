/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structs_initialize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:00 by malluin           #+#    #+#             */
/*   Updated: 2019/05/14 14:35:33 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	initialize_vm(t_vm *vm, int ac)
{
	ft_bzero(vm->players, sizeof(vm->players));
	ft_bzero(vm->arena, sizeof(vm->arena));
	vm->process = NULL;
	vm->players_alive = 0;
	vm->number_of_live = 0;
	vm->last_player_live = 0;
	vm->nb_players = 0;
	vm->nb_process = 0;
	vm->cycles = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_sec = 50;
	vm->current_checks = 0;
	vm->stop = 1;
	vm->dump_cycle = -1;
	vm->enc[0] = 0;
	vm->enc[1] = 1;
	vm->enc[2] = DIR_SIZE;
	vm->enc[3] = IND_SIZE;
	ft_bzero(vm->enc_byte, sizeof(vm->enc_byte));
	ft_bzero(vm->enc_byte_codes, sizeof(vm->enc_byte_codes));
	vm->debug = 0;
	vm->detail = 0;
	vm->ac = ac;
	vm->visu.boite_l = NULL;
	vm->visu.boite_r = NULL;
}

void	add_player(t_vm *vm, char *path, int next_nb, int i)
{
	int		j;

	j = 0;
	while (vm->players[j] != NULL && j < MAX_PLAYERS)
	{
		if (vm->players[j]->player_number == next_nb && next_nb != 0)
			ft_error_already_assigned(vm);
		j++;
	}
	if (j == MAX_PLAYERS)
		ft_error_too_many(vm);
	if (!(vm->players[j] = (t_player *)malloc(sizeof(t_player))))
		exit(-1);
	if (!(vm->players[j]->file_path = ft_strdup(path)))
		vm->players[j]->file_path = NULL;
	vm->players[j]->player_number = next_nb;
	vm->players[j]->code_start = 0;
	vm->players[j]->order_arg = i;
	vm->players[j]->nb_process = 0;
	vm->players[j]->lives_curr = 0;
	vm->players_alive += 1;
	if (!(vm->players[j]->header = (t_header *)malloc(sizeof(t_header))))
		exit(-1);
	ft_bzero(vm->players[j]->header, sizeof(vm->players[j]->header));
}

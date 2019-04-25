/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structs_initialize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:00 by malluin           #+#    #+#             */
/*   Updated: 2019/04/18 18:59:22 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void		initialize_vm(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
		vm->players[i++] = NULL;
	ft_bzero(vm->arena, sizeof(vm->arena));
	// ft_bzero(vm->play_order, MAX_PLAYERS);
	vm->process = NULL;
	vm->cycles = 0;
	vm->players_alive = 0;
	vm->nb_players =0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_sec = 50;
	vm->nb_process = 0;
	vm->stop = 1;
	vm->number_of_live = 0;
	vm->last_player_live = 0;
	vm->dump_cycle = -1;
	vm->visualization = 0;
	vm->enc[0] = 0;
	vm->enc[1] = 1;
	vm->enc[2] = 4;
	vm->enc[3] = 2;
	vm->current_checks = 0;
}

void	add_player(t_vm *vm, char *path, int next_nb, int i)
{
	int		j;

	j = 0;
	while (vm->players[j] != NULL && j < MAX_PLAYERS)
		j++;
	if (j == MAX_PLAYERS)
		ft_error_too_many();
	if (!(vm->players[j] = (t_player *)malloc(sizeof(t_player))))
		exit (-1);
	vm->players[j]->file_path = ft_strdup(path);
	vm->players[j]->player_number = next_nb;
	vm->players[j]->code_start = 0;
	vm->players[j]->order_arg = i;
	vm->players[j]->nb_process = 0;
	vm->players[j]->alive = 1;
	vm->players_alive += 1;
	if (!(vm->players[j]->header = (t_header *)malloc(sizeof(t_header))))
		exit(-1);
	vm->players[j]->header->magic = 0;
	vm->players[j]->header->prog_size = 0;
	ft_bzero(vm->players[j]->header->prog_name, PROG_NAME_LENGTH);
	ft_bzero(vm->players[j]->header->comment, COMMENT_LENGTH);
}

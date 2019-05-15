/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_refresh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:21 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 17:06:21 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	arena_display(t_vm *vm, int run)
{
	int		i;
	int		k;
	int		color;

	i = 0;
	k = vm->visu.b_h + 2;
	move(k, vm->visu.b_w_l + 1);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			printw("  ");
		color = ft_iabs(vm->arena[i].id) + 10 * (vm->arena[i].proc_id != 0)
			+ 100 * (vm->arena[i].st_id > 0);
		if (vm->arena[i].st_id > 0 && run == 1)
			vm->arena[i].st_id -= 1;
		attron(COLOR_PAIR(color));
		printw("%02hhx", vm->arena[i].by);
		attroff(COLOR_PAIR(color));
		printw(" ");
		i = (i % 64) * 3 + 10 > vm->visu.w_l ? i + (64 - i % 64) : i + 1;
		if (i % 64 == 0)
			move(++k, vm->visu.b_w_l + 1);
		if (i / 64 + 3 > LINES)
			break ;
	}
}

void	menu_players(t_vm *vm, int bx, int by)
{
	int		i;
	char	*nm;

	i = 0;
	nm = NULL;
	while (i < vm->nb_players)
	{
		move(bx++, by);
		nm = ft_strsub(vm->players[i]->header->prog_name, 0, vm->visu.w_r - 20);
		printw("Player %d:", vm->players[i]->player_number);
		attron(COLOR_PAIR(i + 1));
		printw(" %s", nm);
		attroff(COLOR_PAIR(i + 1));
		move(bx++, by);
		printw("  Lives in current period: %-7d", vm->players[i]->lives_curr);
		i++;
		bx++;
		ft_memdel((void **)&nm);
	}
}

void	menu(t_vm *vm, int i)
{
	attron(A_BOLD);
	move(vm->visu.b_h + 2, vm->visu.b_w_r + 3);
	printw("---- Welcome to COREWAR ---");
	move(vm->visu.b_h + 4, vm->visu.b_w_r + 3);
	if (vm->stop == 0)
		printw("**** Running ****");
	else
		printw("**** Paused ****");
	move(vm->visu.b_h + i++, vm->visu.b_w_r + 3);
	printw("Current cycle: %-7d", vm->cycles + 1);
	move(vm->visu.b_h + i++, vm->visu.b_w_r + 3);
	printw("Cycle to die: %-4d", vm->cycle_to_die);
	move(vm->visu.b_h + i++, vm->visu.b_w_r + 3);
	printw("Players: %-2d", vm->nb_players);
	move(vm->visu.b_h + i++, vm->visu.b_w_r + 3);
	printw("Process: %-8d", vm->nb_process);
	move(vm->visu.b_h + i++, vm->visu.b_w_r + 3);
	printw("Cycle per sec: %-3d", vm->cycle_sec);
	move(vm->visu.b_h + i++, vm->visu.b_w_r + 3);
	printw("Number of lives: %-6d", vm->number_of_live);
	move(vm->visu.b_h + i++, vm->visu.b_w_r + 3);
	printw("Last player live: %-10d", vm->last_player_live);
	menu_players(vm, vm->visu.b_h + i + 2, vm->visu.b_w_r + 3);
	attroff(A_BOLD);
}

void	borders(t_vm *vm, int to_init)
{
	if (to_init == 1)
	{
		attron(COLOR_PAIR(30));
		attron(A_BOLD);
		if (vm->visu.boite_l != NULL)
			delwin(vm->visu.boite_l);
		if (vm->visu.boite_r != NULL)
			delwin(vm->visu.boite_r);
		vm->visu.boite_l = subwin(stdscr, vm->visu.h, vm->visu.w_l,
			vm->visu.b_h, vm->visu.b_w_l);
		vm->visu.boite_r = subwin(stdscr, vm->visu.h, vm->visu.w_r,
			vm->visu.b_h, vm->visu.b_w_r);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(30));
	}
	wborder(vm->visu.boite_l, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wborder(vm->visu.boite_r, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
}

void	refresh_window(t_vm *vm, int run)
{
	static int		line = -1;
	static int		col = -1;

	if (line != LINES || col != COLS)
	{
		clear();
		vm->visu.b_h = LINES > L_H ? (LINES - L_H) / 2 : 0;
		vm->visu.h = LINES > L_H ? L_H : LINES;
		vm->visu.b_w_l = COLS > R_W + L_W ? (COLS - R_W - L_W) / 2 : 0;
		vm->visu.w_l = COLS < L_W + R_W ? (COLS - R_W) : L_W;
		vm->visu.w_l = vm->visu.w_l < 0 ? 0 : vm->visu.w_l;
		vm->visu.b_w_r = vm->visu.w_l + vm->visu.b_w_l;
		vm->visu.w_r = COLS > R_W ? R_W : COLS;
		line = LINES;
		col = COLS;
		borders(vm, 1);
	}
	arena_display(vm, run);
	menu(vm, 6);
	move(LINES - 1, COLS - 1);
	refresh();
}

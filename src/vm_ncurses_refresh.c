/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_refresh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:21 by malluin           #+#    #+#             */
/*   Updated: 2019/04/19 14:54:45 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm.h"
#include "libft.h"

void	arena_display(t_vm *vm)
{
	int i = 0;
	// int col = 0;
	// char by = 0;

	// attron(A_BOLD);
	move(2,0);
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_CYAN);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(14, COLOR_BLACK, COLOR_RED);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			printw("	");
		attron(COLOR_PAIR(vm->arena[i].id + 10 * (vm->arena[i].proc_id != 0)));
		printw("%02hhx", vm->arena[i].by);
		attroff(COLOR_PAIR(vm->arena[i].id + 10 * (vm->arena[i].proc_id != 0)));
		printw(" ");
		i++;
		if (i % 64 == 0)
			printw("\n");
	}
	// attroff(A_DIM);
}

void	menu(t_vm *vm)
{
	attron(A_BOLD);
	move(2, COLS - COLS/6);
	printw("---- Welcome to COREWAR ---");
	move(4, COLS - COLS/6);
	printw("Cycle passed: %d\n", vm->cycles);
	move(5, COLS - COLS/6);
	printw("Cycle to die: %d\n", vm->cycle_to_die);
	move(6, COLS - COLS/6);
	printw("Players: %d", vm->nb_players);
	move(7, COLS - COLS/6);
	printw("Process: %d", vm->nb_process);
	move(8, COLS - COLS/6);
	printw("Cycle per sec: %d", vm->cycle_sec);
	move(9, COLS - COLS/6);
	printw("Number of lives: %d", vm->number_of_live);
	move(10, COLS - COLS/6);
	printw("Last player live: %d", vm->last_player_live);
	move(15, COLS - COLS/6);
	attroff(A_BOLD);
}

void 	borders()
{
	WINDOW *boite;


	// attron(COLOR_PAIR(1));
	attron(A_BOLD);
	attron(COLOR_PAIR(0));
	border('|', '|', '-', '-', '+', '+', '+', '+');
	// box(boite, ACS_VLINE, ACS_HLINE);
	boite = subwin(stdscr, LINES, COLS * 1 / 4, 0, COLS - COLS / 4);
	wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
	// box(boite, ACS_VLINE, ACS_HLINE);
	ft_memdel((void **)&boite);
	attroff(A_BOLD);
	// attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(0));
}

void	refresh_window(t_vm *vm)
{
	arena_display(vm);
	menu(vm);
	borders();
	move(LINES - 1,COLS - 1);
	refresh();
}

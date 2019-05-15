/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:31 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 17:06:07 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ncurses.h>
#include "libft.h"

void	initialize_color_2(void)
{
	init_pair(113, FLUO_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(14, COLOR_BLACK, COLOR_RED);
	init_pair(104, FLUO_RED, COLOR_BLACK);
	init_pair(114, FLUO_RED, COLOR_BLACK);
	init_pair(30, COLOR_WHITE, COLOR_WHITE);
}

void	initialize_color(void)
{
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		exit(1);
	}
	init_color(FLUO_YELLOW, 1000, 950, 800);
	init_color(FLUO_GREEN, 650, 1000, 650);
	init_color(FLUO_BLUE, 0, 800, 1000);
	init_color(FLUO_RED, 1000, 600, 600);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(101, FLUO_YELLOW, COLOR_BLACK);
	init_pair(111, FLUO_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_GREEN);
	init_pair(102, FLUO_GREEN, COLOR_BLACK);
	init_pair(112, FLUO_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_BLUE);
	init_pair(103, FLUO_BLUE, COLOR_BLACK);
	initialize_color_2();
}

void	initialize_window(t_vm *vm)
{
	initscr();
	start_color();
	initialize_color();
	cbreak();
	nodelay(stdscr, TRUE);
	noecho();
	keypad(stdscr, TRUE);
	refresh_window(vm, 1);
}

void	close_window(t_vm *vm)
{
	delwin(vm->visu.boite_l);
	delwin(vm->visu.boite_r);
	endwin();
	end_game(vm);
}

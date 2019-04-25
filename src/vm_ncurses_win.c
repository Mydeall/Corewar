/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:31 by malluin           #+#    #+#             */
/*   Updated: 2019/04/17 11:34:22 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ncurses.h>

void	initialize_window(t_vm *vm)
{
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	cbreak();
	nodelay(stdscr, TRUE);
	noecho();
	keypad(stdscr, TRUE);
	refresh_window(vm);
}

void	close_window()
{
	endwin();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 10:59:53 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 17:04:12 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

void	read_files(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->players[i] != NULL)
			vm_read_byte(vm->players[i], vm);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_vm	*vm;

	if (ac <= 1)
		ft_usage();
	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	initialize_vm(vm, ac);
	vm->ncurses = 0;
	ft_parse_args(vm, ac, av, 1);
	vm->detail = vm->ncurses == 1 ? 0 : vm->detail;
	read_files(vm);
	create_processes(vm);
	if (vm->ncurses == 1)
	{
		initialize_window(vm);
		main_loop(vm);
		close_window(vm);
	}
	else
	{
		print_intro(vm);
		main_loop(vm);
		end_game(vm);
	}
	return (0);
}

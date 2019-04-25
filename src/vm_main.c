/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 10:59:53 by malluin           #+#    #+#             */
/*   Updated: 2019/04/22 14:07:36 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"
#include "libftprintf.h"

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
	// fix_play_order(vm, 0, 0);
	// printf("%d %d %d %d\n\n", vm->play_order[0], vm->play_order[1], vm->play_order[2], vm->play_order[3]);
}

void	p_run(t_vm *vm, t_process *p, int pc)
{
	//choose the function on the byte
	//wait function
	int				count;

	count = 0;
	pc = p->pc;
	ft_printf("current byte value \n%02hhx\n", vm->arena[pc].by);
	pc++;
	// op_load(vm, p, pc);
	// while (count < REG_SIZE)
	// {
	// 	p->regs[5][count] = 5;
	// 	count++;
	// }
	op_store(vm, p);
	ft_print_process(vm);
}

int		main(int ac, char **av)
{
	t_vm	*vm;

	if (ac <= 1)
		ft_usage();
	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	initialize_vm(vm);
	if (ft_parse_args(vm, ac, av) == -1)
		return (0);
	read_files(vm);
	create_processes(vm);
	ft_print_players(vm);


	// ft_print_xarena(vm, 50);
	// t_process *p = vm->process;
	ft_print_process(vm);
	// //1 correspond q lendorit ou il faudra mettre pc, l avancement dans la memoire
	// p_run(vm, p, 0);
	// exit(0);

	if (vm->visualization == 1)
	{
		initialize_window(vm);
		main_loop(vm);
		close_window();
	}
	else
	{
		print_intro(vm);
		main_loop(vm);
	}
	return (0);
}

// void	fix_play_order(t_vm *vm, int i, int idx)
// {
// 	int		max;
// 	int		j;
// 	int		prevmax;
//
// 	i = 0;
// 	idx = 0;
// 	prevmax = 0;
// 	while (i < vm->players_alive)
// 	{
// 		j = -1;
// 		max = 0;
// 		while (++j < vm->players_alive)
// 		{
// 			if (vm->players[j]->order_arg > max && (prevmax == 0
// 				|| vm->players[j]->order_arg < prevmax))
// 			{
// 				max = vm->players[j]->order_arg;
// 				idx = j;
// 				prevmax = max;
// 			}
// 		}
// 		vm->play_order[i++] = idx;
// 	}
// }

// Surement useless fix_play_order car au final l'ordre de creation des joueurs est en fonction de leur ordre en argv
// donc suffit de boucler de facon decroissante pour avoir le bon ordre

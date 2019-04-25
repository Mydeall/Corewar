/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:16:01 by malluin           #+#    #+#             */
/*   Updated: 2019/04/17 19:20:55 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		file_exists(char *path)
{
	int		fd;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	if (read(fd, NULL, 0) == -1)
		return (0);
	close(fd);
	return (1);
}

void	reorder_players(t_vm *vm)
{
	int		j;
	int		c;
	int		to_assign;

	to_assign = 1;
	c = 0;
	while (c < vm->players_alive)
	{
		j = 0;
		while (j < vm->players_alive && vm->players[j] != NULL)
		{
			if (vm->players[j++]->player_number == to_assign)
			{
				to_assign++;
				j = 0;
				continue;
			}
		}
		if (vm->players[c] != NULL && vm->players[c]->player_number == 0)
			vm->players[c]->player_number = to_assign;
		c++;
	}
	vm->nb_players = vm->players_alive;
}

int		read_player_number(char *str)
{
	long long nb;

	nb = ft_atol(str);
	if (nb < 0 || nb > 2147483647 || ft_strlen(str) > 11)
		ft_incorrect_number();
	return ((int)nb);
}

int		ft_parse_args(t_vm *vm, int ac, char **av)
{
	int		i;
	int		next_nb;

	i = 1;
	next_nb = 0;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-dump") == 0)
		{
			if (i++ == ac - 1)
				ft_error_read("-dump");
			else
				vm->dump_cycle = ft_atoi(av[i++]);
		}
		else if (ft_strcmp(av[i], "-n") == 0)
		{
			if (i++ >= ac - 2)
				ft_error_read("-n");
			else
				next_nb = read_player_number(av[i++]);
			if (file_exists(av[i]) == 0)
				ft_error_read(av[i]);
		}
		else if (ft_strcmp(av[i], "-v") == 0)
		{
			vm->visualization = 1;
			i++;
		}
		else
		{
			if (file_exists(av[i]) == 0)
				ft_error_read(av[i]);
			add_player(vm, av[i], next_nb, i);
			next_nb = 0;
			i++;
		}
	}
	reorder_players(vm);
	return (1);
}

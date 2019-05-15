/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:16:01 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 16:37:38 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		file_exists(t_vm *vm, char *path)
{
	int		fd;
	int		size;
	char	tmp[2192 + CHAMP_MAX_SIZE + 1];

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	if (read(fd, NULL, 0) == -1)
		return (0);
	size = read(fd, tmp, 2192 + CHAMP_MAX_SIZE + 1);
	if (size < 2192)
		error_champ_too_small(vm);
	else if (size > 2192 + CHAMP_MAX_SIZE)
		error_champ_too_big(vm);
	close(fd);
	return (1);
}

void	reorder_players(t_vm *vm)
{
	int		j;
	int		c;
	int		to_assign;

	to_assign = 1;
	c = -1;
	if (vm->players_alive <= 0)
		ft_usage();
	while (++c < vm->players_alive)
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
	}
	vm->nb_players = vm->players_alive;
	vm->last_player_live = vm->players[c - 1]->player_number;
}

int		read_player_number(t_vm *vm, char *str)
{
	long long nb;

	nb = ft_atol(str);
	if (nb <= 0 || nb > 2147483647 || ft_strlen(str) > 11)
		ft_incorrect_number(vm);
	return ((int)nb);
}

void	ft_parse_args_2(t_vm *vm, char **av, int *next_nb, int *i)
{
	if (ft_strcmp(av[*i], "-g") == 0)
	{
		vm->ncurses = 1;
	}
	else if (ft_strcmp(av[*i], "-v") == 0)
	{
		*i += 1;
		if ((*i - 1) == vm->ac - 1)
			ft_error_read(vm, "-v");
		else
			vm->detail = ft_atoi(av[*i]);
	}
	else if (ft_strcmp(av[*i], "-d") == 0)
		vm->debug = 1;
	else
	{
		if (file_exists(vm, av[*i]) == 0)
			ft_error_read(vm, av[*i]);
		add_player(vm, av[*i], *next_nb, *i);
		*next_nb = 0;
	}
	*i += 1;
}

void	ft_parse_args(t_vm *vm, int ac, char **av, int i)
{
	int		next_nb;

	next_nb = 0;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-dump") == 0)
		{
			if (i++ == ac - 1)
				ft_error_read(vm, "-dump");
			else
				vm->dump_cycle = ft_atoi(av[i++]);
		}
		else if (ft_strcmp(av[i], "-n") == 0)
		{
			if (i++ >= ac - 2)
				ft_error_read(vm, "-n");
			else
				next_nb = read_player_number(vm, av[i++]);
			if (file_exists(vm, av[i]) == 0)
				ft_error_read(vm, av[i]);
		}
		else
			ft_parse_args_2(vm, av, &next_nb, &i);
	}
	reorder_players(vm);
}

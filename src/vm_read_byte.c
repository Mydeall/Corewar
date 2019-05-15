/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_byte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:39:44 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/10 17:04:01 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libft.h"
#include "fcntl.h"

void	put_player(t_vm *vm, t_player *player, unsigned char *buff, int idx)
{
	unsigned int	i;
	int				zero;
	static int		nb_players = 5;

	i = 0;
	nb_players = nb_players == 5 ? vm->nb_players : nb_players;
	if (vm->players_alive == 0)
		return ;
	zero = MEM_SIZE / vm->players_alive * (vm->players_alive - nb_players--);
	player->code_start = zero;
	while (i < CHAMP_MAX_SIZE && i < player->header->prog_size)
	{
		ft_memmove(&vm->arena[(zero + i + MEM_SIZE) % MEM_SIZE].by,
			&buff[i], 1);
		vm->arena[(zero + i + MEM_SIZE) % MEM_SIZE].id = idx;
		i++;
	}
}

void	check_errors(t_vm *vm, unsigned char *buff, int res, char test)
{
	if (res > 0 && test != '\0')
	{
		ft_memdel((void **)&buff);
		error_champ_too_big(vm);
	}
	else if (res == -1)
	{
		ft_memdel((void **)&buff);
		error_read(vm);
	}
}

void	read_player_code(int fd, t_player *player, t_vm *vm)
{
	unsigned char	*buff;
	char			test;
	int				res;
	static int		idx = 1;

	if (!(buff = (unsigned char *)malloc(sizeof(unsigned char)
		* (CHAMP_MAX_SIZE + 1))))
		exit(-1);
	ft_bzero(buff, CHAMP_MAX_SIZE);
	res = read(fd, buff, CHAMP_MAX_SIZE);
	if (res == -1 || res != (int)player->header->prog_size)
	{
		ft_memdel((void **)&buff);
		error_wrong_weight(vm);
	}
	res = read(fd, &test, 1);
	if (res == -1 || player->header->magic != 15369203 || (res > 0))
		check_errors(vm, buff, res, test);
	else
	{
		put_player(vm, player, buff, idx++);
		ft_memdel((void **)&buff);
	}
}

void	vm_read_byte(t_player *player, t_vm *vm)
{
	int				fd;
	unsigned char	*tmp;

	if (!(tmp = (unsigned char *)malloc(sizeof(unsigned char) * (4))))
		exit(-1);
	ft_bzero(tmp, 4);
	fd = open(player->file_path, O_RDONLY);
	if (fd == -1 || read(fd, tmp, sizeof(unsigned int)) == -1)
		error_read(vm);
	player->header->magic = tmp[3] + (tmp[2] << 8) + (tmp[1] << 16)
		+ (tmp[0] << 24);
	if (player->header->magic != 15369203)
		error_wrong_header(vm);
	read(fd, player->header->prog_name, PROG_NAME_LENGTH);
	read(fd, tmp, 4);
	ft_bzero(tmp, 4);
	read(fd, tmp, sizeof(unsigned int));
	player->header->prog_size = tmp[3] + (tmp[2] << 8) + (tmp[1] << 16)
		+ (tmp[0] << 24);
	read(fd, player->header->comment, COMMENT_LENGTH);
	read(fd, tmp, 4);
	ft_memdel((void **)&tmp);
	read_player_code(fd, player, vm);
}

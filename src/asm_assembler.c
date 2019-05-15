/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_assembler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:35:43 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/14 16:07:16 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	verif_name(char *file_name)
{
	int		i;

	if (!(*file_name))
		return (1);
	i = (int)ft_strlen(file_name);
	while (--i)
		if (file_name[i] == '/')
		{
			i++;
			break ;
		}
	if (file_name[i] == '.')
		return (1);
	while (file_name[++i])
		if (file_name[i] == '.')
			break ;
	if (ft_strcmp(&(file_name[i]), ".s"))
		return (1);
	return (0);
}

int			main(int ac, char **av)
{
	int		fd;
	t_token	*tokens;
	t_token *labels;
	t_instr	*instructions;
	int		ret;

	tokens = NULL;
	labels = NULL;
	instructions = NULL;
	if (ac < 2 || verif_name(av[ac - 1]))
		return (print_arg_error((ac < 2), av[0]));
	if ((fd = open(av[ac - 1], O_RDONLY)) == -1)
		return (print_sys_error(errno));
	if ((ret = scanner_asm(fd, &tokens, &labels))\
			|| (ret = parser_asm(&tokens, &instructions, labels))\
			|| (ret = encoder_asm(instructions, labels, av[ac - 1])))
	{
		if (ret == -1)
			print_sys_error(errno);
		free_manager(tokens, instructions, labels, fd);
		return (1);
	}
	return (free_manager(tokens, instructions, labels, fd));
}

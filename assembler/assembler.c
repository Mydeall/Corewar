/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:40:32 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/08 17:59:27 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	verif_name(char *file_name)
{
	int		i;

	if (!(*file_name) || *file_name == '.')
		return (1);
	i = -1;
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
		free_manager(tokens, instructions, labels);
		return (1);
	}
	free_manager(tokens, instructions, labels);
	return (0);
}

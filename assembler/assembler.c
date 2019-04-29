/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:40:32 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/29 20:09:53 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
void	free_manager(t_token *tokens, t_instr *instructions)
{
	t_token	*tmp;
	t_instr	*tmp2;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free_token(&tmp);
	}
	while (instructions)
	{
		tmp2 = instructions;
		instructions = instructions->next;
		free(instructions); // a remplacer par la fonction adaptee
	}
}

int		main(int ac, char **av)
{
	int		fd;
	t_token	*tokens;
	t_token *labels;
	t_instr	*instructions;

	tokens = NULL;
	labels = NULL;
	instructions = NULL;
	if (ac < 2)
		return(print_arg_error(1));
	if ((fd = open(av[ac - 1], O_RDONLY)) == -1)
		return (print_system_error(errno));
	if (scanner_asm(fd, &tokens, &labels)
	   	|| parser_asm(&tokens, &instructions, labels)
									/*	|| !encoder_asm(instructions)  */)
	{
//		check_tokens(tokens);
		free_manager(tokens, instructions);
		return (1);
	}
	check_instructions(instructions);
	free_manager(tokens, instructions);
	return(0);
}	

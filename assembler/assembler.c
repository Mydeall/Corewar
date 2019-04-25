/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:40:32 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/25 16:40:09 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_tokens(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		printf("---token no %d:---\n", i);
		printf("type = %d\n", tokens->lexem);
		printf("value = %s\n", tokens->value);
		i++;
		tokens = tokens->next;
	}
}

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
	t_instr	*instructions;

	tokens = NULL;
	instructions = NULL;
	if (ac < 2)
		return(print_arg_error(1));
	if ((fd = open(av[ac - 1], O_RDONLY)) == -1)
		return (print_system_error(errno));
	if (scanner_asm(fd, &tokens)
	   	/*|| parser_asm(tokens, instructions) <= 0
										|| !encoder_asm(instructions)  */)
	{
		check_tokens(tokens);
		free_manager(tokens, instructions);
		return (1);
	}
	check_tokens(tokens);
	free_manager(tokens, instructions);
	return(0);
}	

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:36:52 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 17:37:03 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_token(t_token *token)
{
	ft_printf("type = ");
	print_lexem(token->lexem);
	ft_printf("\n");
	ft_printf("value = |%s|\n", token->value);
	ft_printf("inst_address = |%d|\n", token->inst_address);
	ft_printf("address = |%d|\n", token->address);
	ft_printf("line = %d\n", token->line);
	ft_printf("col = %d\n", token->col);
}

void	check_tokens(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		ft_printf("---token no %d:---\n", i);
		print_token(tokens);
		i++;
		tokens = tokens->next;
	}
}

void	check_instructions(t_instr *instructions)
{
	int		i;
	t_token	*current_token;

	i = 0;
	while (instructions)
	{
		ft_printf("---instruction no %d:---\n", i);
		if (instructions->opcode == 0)
			ft_printf("name | comment token\n");
		else
			ft_printf("opcode = %s\n", g_op_tab[instructions->opcode - 1].inst);
		current_token = instructions->params;
		while (current_token)
		{
			print_lexem(current_token->lexem);
			ft_printf("\n");
			ft_printf("address = %d\n", current_token->address);
			if (current_token->next)
				ft_printf("->");
			current_token = current_token->next;
		}
		ft_printf("\n");
		instructions = instructions->next;
		i++;
	}
}

void	print_tokens(t_token *tokens)
{
	int		i;
	t_token	*current;

	current = tokens;
	i = 0;
	while (current)
	{
		ft_printf("token %d : %p\n", i, current);
		current = current->next;
		if (current && current == current->next)
		{
			ft_printf("token %d : %p\n", i + 1, current->next);
			ft_printf("boucle\n");
			break ;
		}
		i++;
	}
}

void	print_lexem(t_lex lexem)
{
	if (lexem == DIRECT)
		ft_printf("[DIRECT]");
	if (lexem == INDIRECT)
		ft_printf("[INDIRECT]");
	if (lexem == REGISTER)
		ft_printf("[REGISTER]");
	if (lexem == NAME)
		ft_printf("[NAME]");
	if (lexem == COMMENT)
		ft_printf("[COMMENT]");
	if (lexem == CARRIAGE)
		ft_printf("[CARRIAGE RETURN]");
	if (lexem == LABEL)
		ft_printf("[LABEL]");
	if (lexem == OPCODE)
		ft_printf("[OPCODE]");
	if (lexem == COMMA)
		ft_printf("[COMMA]");
	if (lexem == NONE)
		ft_printf("[NONE]");
}

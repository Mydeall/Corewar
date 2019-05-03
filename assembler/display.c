/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:39:12 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/03 18:13:51 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_token(t_token *token)
{
	printf("type = %d\n", token->lexem);
	printf("value = |%s|\n", token->value);
}

void	check_tokens(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		printf("---token no %d:---\n", i);
		printf("type = %d\n", tokens->lexem);
		printf("value = %s\n", tokens->value);
		printf("line = %d\n", tokens->line);
		printf("col = %d\n", tokens->col);
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
		printf("---instruction no %d:---\n", i);
		if (instructions->opcode == 0)
			printf("name | comment token\n");
		else
			printf("opcode = %s\n", g_op_tab[instructions->opcode - 1].inst);
		current_token = instructions->params;
		while (current_token)
		{
			print_lexem(current_token->lexem);
			if (current_token->next)
				printf("->");
			current_token = current_token->next;
		}
		printf("\n");
		instructions = instructions->next;
		i++;
	}
}

void	print_tokens(t_token *tokens)
{
	int i;
	t_token *current;

	current = tokens;
	i = 0;
	while (current)
	{
		printf("token %d : %p\n", i, current);
		current = current->next;
		if (current && current == current->next)
		{
			printf("token %d : %p\n", i + 1, current->next);
			printf("boucle\n");
			break ;
		}
		i++;
	}

}

void	print_lexem(t_lex lexem)
{
	if (lexem == DIRECT)
		printf("[DIRECT]");
	if (lexem == INDIRECT)
		printf("[INDIRECT]");	
	if (lexem == REGISTER)
		printf("[REGISTER]");
	if (lexem == NAME)
		printf("[NAME]");
	if (lexem == COMMENT)
		printf("[COMMENT]");
	if (lexem == CARRIAGE)
		printf("[CARRIAGE RETURN]");
	if (lexem == LABEL)
		printf("[LABEL]");
	if (lexem == OPCODE)
		printf("[OPCODE]");
	if (lexem == COMMA)
		printf("[COMMA]");
}

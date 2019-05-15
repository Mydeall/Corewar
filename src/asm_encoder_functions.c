/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_encoder_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:37:36 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 17:37:47 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	complete_labels(t_writer *writer, t_token *label, t_token *labels)
{
	t_token	*current;

	while (label)
	{
		current = labels;
		while (current)
		{
			if (!(ft_strcmp(label->value, current->value)))
			{
				current->inst_address = writer->address + writer->cursor;
				break ;
			}
			current = current->next;
		}
		label = label->next;
	}
}

int		give_size_param(int opcode, t_lex lexem)
{
	if (lexem == REGISTER)
		return (1);
	if (lexem == INDIRECT)
		return (2);
	return (g_op_tab[opcode - 1].dir_size);
}

void	replace_label_value(t_writer *writer, t_token *labels, t_token *queue)
{
	t_token	*current_label;

	while (queue)
	{
		current_label = labels;
		while (current_label\
			&& ft_strcmp(queue->value + 1, current_label->value))
			current_label = current_label->next;
		insert_value(&(writer->output[queue->address]),\
				(unsigned int)(current_label->inst_address -\
					queue->inst_address), queue->size);
		queue = queue->next;
	}
}

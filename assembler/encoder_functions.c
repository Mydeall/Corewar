/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:38:12 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/03 14:11:50 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	complete_labels(t_writer *writer, char *label, t_token *labels)
{
	while (labels)
	{
		if (!(ft_strcmp(label, labels->value)))
		{
			labels->inst_address = writer->address + writer->cursor;
			break ;
		}
		labels = labels->next;
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

	printf("replace label\n");
	while (queue)
	{
		current_label = labels;		
		while (current_label\
			&& ft_strcmp(queue->value + 1, current_label->value))
			current_label = current_label->next;
		printf("label address: %d\n", current_label->inst_address);
		printf("queue adresses : %d\n", queue->inst_address);
		printf("Diff d adresses : %u\n", (unsigned int)(current_label->inst_address - queue->inst_address));
		printf("Diff aueue->size : %d\n", queue->size);
		insert_value(&(writer->output[queue->address]),
					(unsigned int)(current_label->inst_address - queue->inst_address), 
					queue->size);
		queue = queue->next;
	}
}

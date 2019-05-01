/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:38:12 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/01 16:59:02 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	complete_labels(t_writer *writer, char *label, t_token *labels)
{
	while (labels)
	{
		if (!(ft_strcmp(label, labels->value)))
		{
			labels->address = writer->address;
			break ;
		}
		labels = labels->next;
	}
}

int		give_size_param(int opcode, t_lex lexem)
{
	if (lexem == REGISTER)
		return (1 * 8);
	if (lexem == INDIRECT)
		return (2 * 8);
	return (g_op_tab[opcode - 1].dir_size * 8);
}

void	replace_label_value(t_writer *writer, t_token *labels, t_token *queue)
{
	t_token	*current_label;
	int		i;

	while (queue)
	{
		current_label = labels;		
		while (current_label\
			&& ft_strcmp(queue->value + 1, current_label->value))
			current_label = current_label->next;
		i = 0;
		while (writer->output[i + queue->address * 8]
			   	== writer->output[i + 1 + queue->address * 8])
			i++;
		i++;
		int_to_bytes(&(writer->output[queue->address * 8]),
					(unsigned int)(current_label->address - queue->address), i);
		queue = queue->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:55:02 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/30 18:43:14 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


/*
void	write_header(t_instr **instructions, t_writer *writer)
{
	while 
}
*/	

int		concat_output(t_writer *writer)
{
	if (!(writer->output = ft_strnappend(writer->output, writer->buff,\
				writer->cursor + 1)))
		return (1)
	writer->cursor = 0;
	return (0);
}


int		int_to_bytes(t_writer *writer, unsigned int nb, size_t size)
{
	int max;

	if (BUFF_SIZE_W - writer->cursor + 1 < size)
		if (concat_output(writer))
			return (print_sys_error(errno));
	max = ft_pow(2, size * 8 - 1)
	while (nb)
	{
		writer->buff[writer->cursor++] = nb >= max ? '1' : '0';
		if (nb >= max)
			nb = nb - max;
		max = max / 2;
	}
}

void	complete_label(t_writer *writer, char *label, t_token *labels)
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

int		encoding_byte(t_writer *writer, t_instr *instruction)
{
	t_token	*current_param;
	int		i;

	i = 0;
	if (BUFF_SIZE_W - writer->cursor + 1 < 8)
		if (concat_output(writer))
			return (print_sys_error(errno));
	current_param = instruction->params;
	while (current_param)
	{
		i++;
		writer->buff[writer->cursor++] = current_param->lexem == REGISTER ?\
			'0' : '1';
		writer->buff[writer->cursor++] = current_param->lexem == DIRECT ?\
			'0' : '1';
		current_param = current_param->next;
	}
	i *= 2;
	while (i < 9)
		writer->buff[writer->cursor++] = '0';
	return (0);
}

int		give_size_param(t_instr *instruction, )
g_op_tab[instruction->opcode - 1][3]

int		encode_params(t_writer *writer, t_instr *instruction)
{
	t_token			*current;
	unsigned int	nb;
	int				len;
	int				id;

	id = 2;
	while (current)
	{
		len = give_size_param;
		if (*(current->value) == ':')
		{
			while (--len)
				writer->buff[writer->cursor++] = id + '0';
			continue ;
		}
		nb = ft_atoi(current->value);
		nb = len == 2 * 8 ? (short int)nb : nb;
		if (int_to_byte(writer, nb,	len))
			return (-1);
	}
	return (0);
}

int		encoder_asm(t_instr *instructions, t_token *labels)
{
	t_writer	writer;
	t_token		*queue;

	writer.cursor = 0;
	writer.output = NULL;
	writer.address = 0;
	queue = NULL;
//	write_header(&instructions);
	while (instructions)
	{
		if (instructions->label)
			complete_label(&writer, instructions->label, labels);
		if (int_to_byte(&writer, instructions->opcode, 1))
			return (-1);
		if (g_op_tab[instructions->opcode - 1].enc_byte\
				&& encoding_byte(&writer, instructions))
			return (-1);
		if (encode_params(&writer, instructions))
			return (-1);
		instructions = instructions->next
	}
	if (concat_output(&writer))
		return (-1);
	complete_label(writer, labels);
	if (write_output(writer))
		return (-1);
	return (0);
}

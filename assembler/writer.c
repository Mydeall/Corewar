/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:54:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/03 18:32:34 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		write_text(t_writer *writer, char *text, size_t len)
{
	int		i;

	i = -1;
	while (text[++i] && i < (int)len)
		if (write_into_buffer(writer, text[i], 1))
			return (1);
	i--;
	while (++i < (int)len)
		if (write_into_buffer(writer, 0, 1))
			return (1);	
	return (0);
}

int		concat_output(t_writer *writer)
{
	int i;

	if (!writer->output)
	{
		if (!(writer->output = (char*)malloc(writer->cursor)))
			return (1);
	}
	else
		if (!(writer->output = (char*)realloc(writer->output,
						writer->address + writer->cursor)))
			return (1);
	i = -1;
	while (++i < (int)writer->cursor)
		writer->output[writer->address++] = writer->buff[i];
	writer->cursor = 0;
	return (0);
}

void	insert_value(char *str, unsigned int value, int size)
{
	int i;
	
	i = -1;
	while (++i < size)
		str[i] = value >> (size * 8 - (i + 1) * 8) & 0xFF;
}

int		write_into_buffer(t_writer *writer, unsigned int nb, size_t size)
{
	if (BUFF_SIZE_W - (writer->cursor + 1) < size)
		if (concat_output(writer))
			return (1);
	insert_value(&(writer->buff[writer->cursor]), nb, size);
	writer->cursor += size;
	return (0);
}

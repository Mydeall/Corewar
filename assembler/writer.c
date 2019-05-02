/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:54:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/02 19:39:19 by rkirszba         ###   ########.fr       */
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

	i = -1;
	printf("********\n********\n********\n");
	while (++i < (int)writer->cursor)
		printf("buff char %d : %d\n", i, writer->buff[i]);
	printf("realloc \n");
	if (!writer->output)
	{
		if (!(writer->output = (char*)malloc(writer->cursor)))
			return (1);
	}
	else
		if (!(writer->output = (char*)realloc(writer->output,
						writer->address + writer->cursor)))
			return (1);
	printf("realloc done\n");
	printf("adress : %zu | curosr : %zu\n", writer->address , writer->cursor);
	i = -1;
	while (++i < (int)writer->cursor)
	{
		printf("char %d : %d\n", i, writer->buff[i]);
		writer->output[writer->address++] = writer->buff[i];
	}
	printf("cp done\n");
	writer->cursor = 0;
	printf("********\n********\n********\n");
	return (0);
}

/*
void	int_to_bytes(char *str, unsigned int nb, size_t size)
{
	unsigned long int max;

	printf("nb : %u\n", nb);
	max = (unsigned long int)ft_llpower(2, size - 1);
	printf("binaire (%lu) : ", max);
	while (nb)
	{
		*(str) = nb >= max ? '1' : '0';
		printf("%d | %lu -> %c\n", nb, max, *str);
		str++;
		if (nb >= max)
			nb = nb - max;
		max = max / 2;
		if (max == 0 && nb != 0)
		{
			printf("WTF !\n");
			break ;
		}
	}
	while (max)
	{
		*(str++) = '0';
		max = max / 2;
	}
	printf("\n");
}
*/

void	insert_value(char *str, unsigned int value, int size)
{
	int i;
	
	i = -1;
	while (++i < size)
	{
		str[i] = value >> (size * 8 - (i + 1) * 8) & 0xFF;
		printf("char : %d\n", (unsigned char)str[i]);
	}
}

int		write_into_buffer(t_writer *writer, unsigned int nb, size_t size)
{
	int i;

	printf("-------- WRITE BUFF ------\n");
	printf("size : %zu\n", size);
	printf("cursor : %zu\n", writer->cursor);
	printf("BUFF size: %d\n", BUFF_SIZE_W);
	printf("compute : %lu\n", BUFF_SIZE_W - (writer->cursor + 1));
	if (BUFF_SIZE_W - (writer->cursor + 1) < size)
	{
		printf("stop -> concat\n");
		if (concat_output(writer))
			return (1);
	}
	printf("cursor : %zu\n", writer->cursor);
	insert_value(&(writer->buff[writer->cursor]), nb, size);
	printf("nb : %d | size = %zu\n", nb, size);
	i = -1;
	while (++i < (int)size)
		printf("buff char %d : %d\n", i, writer->buff[writer->cursor + i]);
	writer->cursor += size;
	printf("cursor : %zu\n", writer->cursor);
//	write (1, writer->buff, (int)writer->cursor);
//	printf("\n");
//	printf("buff :\n%.*s\n", (int)writer->cursor, writer->buff);
	return (0);
}

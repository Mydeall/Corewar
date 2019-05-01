/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:54:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/01 16:59:03 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		write_text(t_writer *writer, char *text, size_t len)
{
	int		i;

	i = -1;
	while (text[++i] && i < (int)len)
		if (write_into_buffer(writer, text[i], 1 * 8))
			return (1);
	i = -1;
	while (++i < (int)len)
		if (write_into_buffer(writer, 0, 1 * 8))
			return (1);	
	return (0);
}

int		concat_output(t_writer *writer)
{
	if (ft_strnappend(&(writer->output), writer->buff,\
			writer->cursor + 1))
		return (1);
	writer->cursor = 0;
	return (0);
}

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

int		write_into_buffer(t_writer *writer, unsigned int nb, size_t size)
{
	printf("-------- WRITE BUFF ------\n");
	printf("size : %zu\n", size);
	printf("cursor : %zu\n", writer->cursor);
	if (BUFF_SIZE_W - writer->cursor + 1 < size)
		if (concat_output(writer))
			return (print_sys_error(errno));
	printf("cursor : %zu\n", writer->cursor);
	int_to_bytes(&(writer->buff[writer->cursor]), nb, size);
	writer->cursor += size;
	writer->address += size / 8;
	printf("cursor : %zu\n", writer->cursor);
//	write (1, writer->buff, (int)writer->cursor);
//	printf("\n");
	printf("buff :\n%.*s\n", (int)writer->cursor, writer->buff);
	return (0);
}

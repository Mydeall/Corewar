/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:55:02 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/30 20:10:45 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


int		write_text(t_writer *writer, char *text, size_t size)
{
	int		i;

	i = -1;
	while (text[++i] && i < size)
	   if (int_to_bytes(writer, text[i], 1 * 8))
		   return (1);
	i--;//juste ?
	while (++i < size)
	   if (int_to_bytes(writer, '0', 1 * 8))
		   return (1);
	return (0);
}


int		write_header(t_instr **instructions, t_writer *writer)
{
	int		i;
	
	int_to_bytes(writer, COREWAR_EXEC_MAGIC, 4 * 8);
   	if (write_text(writer, (*instructions)->label, PROG_NAME_LENGTH))
		return (1);
	*instruction = (*instructions)->next;
	if (int_to_bytes(writer, '0', 4 * 8))
	   return (1);
	i = -1;
	while (++i < 4 * 8)
		writer->buff[writer->cursor++] = '5';
	//voir comment gerer l adresse
   	if (write_text(writer, (*instructions)->label, COMMENT_LENGTH))
		return (1);
	*instruction = (*instructions)->next;
	if (int_to_bytes(writer, '0', 4 * 8))
	   return (1);	
}	

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
	//proposition :
	writer->address += size / 4;
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
	// proposition
	(writer->address)++;
	return (0);
}

int		give_size_param(int opcode, t_lex lexem)
{
	if (lexem == REGISTER)
		return (1 * 8);
	if (lexem == INDIRECT)
		return (2 * 8);
	return (g_op_tab[opcode - 1][3] * 8);
}

int		append_queue(t_token **queue, t_token *token)
{
	t_token	*new;
	t_token	*current;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (1);
	if (!(new->value = ft_strdup(token->value)))
	{
		free(new);
		return (1);
	}
	new->lexem = token->lexem;
	new->address = token->address;
	new->next = NULL;
	if (!(*queue))
	{
		*queue = new;
		return (0);
	}
	current = *queue;
	while (current->next)
		current = current->next;
	current->next = new;
	return (0);
}


int		encode_params(t_writer *writer, t_instr *instruction, t_token **queue)
{
	t_token			*current;
	unsigned int	nb;
	int				len;
	int				id;

	id = 2;
	while (current)
	{
		current->address = writer->address // il faut s occuper de l adresse;
		len = give_size_param(instruction->opcode, current->lexem);
		if (*(current->value) == ':')
		{
			if (append_queue(queue, current))
				return (1);	
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
	if (write_header(&instructions))
		return (1);
	while (instructions)
	{
		if (instructions->label)
			complete_label(&writer, instructions->label, labels);
		if (int_to_byte(&writer, instructions->opcode, 1))
			return (-1);
		if (g_op_tab[instructions->opcode - 1].enc_byte\
				&& encoding_byte(&writer, instructions))
			return (-1);
		if (encode_params(&writer, instructions, &queue))
			return (-1);
		instructions = instructions->next
	}
	if (concat_output(&writer))
		return (-1);
	complete_size(writer); // on doit indiquer la size de nos instructions
	complete_label(writer, labels);
	if (write_output(writer))
		return (-1);
	return (0);
}

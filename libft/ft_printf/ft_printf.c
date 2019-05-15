/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:06:56 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/14 16:19:11 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		ft_arg(const char *restrict *format,\
	t_struct_tab struct_tab, int len, va_list ap)
{
	int		i;

	node_reset(&struct_tab.stack);
	if ((i = ft_format_parser(*format, &struct_tab.stack,\
					struct_tab, ap)) == -1)
		return (-1);
	*format = &(*format)[i];
	if ((len = ft_stack_applier(&struct_tab.stack, struct_tab, ap, &len)) == -1)
		return (-1);
	free_node(&struct_tab.stack);
	return (len);
}

void				concat_buff(char **buff, char *str, int i,\
		int *len)
{
	int j;

	j = -1;
	while (++j < i)
	{
		(*buff)[(*len % BUFF_SIZE) + j] = str[j];
		if ((*len % BUFF_SIZE) + j == BUFF_SIZE)
		{
			write(1, *buff, BUFF_SIZE);
			*len += j;
			i -= j;
			j = -1;
		}
	}
	*len += j;
}

static t_struct_tab	make_struct_tab(void)
{
	t_struct_tab	struct_tab;
	t_stack			stack;
	char			*buff;

	buff = (char*)malloc(BUFF_SIZE);
	node_reset(&stack);
	struct_tab.stack = stack;
	struct_tab.format_tab = make_format_tab();
	struct_tab.call_format = make_call_format();
	struct_tab.call_attr = make_call_attr();
	struct_tab.buff = buff;
	return (struct_tab);
}

static void			end_printf(t_struct_tab struct_tab, int len)
{
	write(1, struct_tab.buff, len % BUFF_SIZE);
	free(struct_tab.format_tab);
	struct_tab.format_tab = NULL;
	free(struct_tab.call_format);
	struct_tab.call_format = NULL;
	free(struct_tab.call_attr);
	struct_tab.call_attr = NULL;
	ft_strdel(&struct_tab.buff);
}

int					ft_printf(const char *restrict format, ...)
{
	int				i;
	int				len;
	t_struct_tab	struct_tab;
	va_list			ap;

	if (!(format))
		return (0);
	struct_tab = make_struct_tab();
	if (!struct_tab.buff)
		return (0);
	va_start(ap, format);
	len = 0;
	i = -1;
	while (format[++i])
		if (format[i] == '%')
		{
			concat_buff(&struct_tab.buff, (char*)format, i, &len);
			format = &format[i];
			i = -1;
			if ((len = ft_arg(&format, struct_tab, len, ap)) == -1)
				return (-1);
		}
	concat_buff(&struct_tab.buff, (char*)format, i, &len);
	end_printf(struct_tab, len);
	return (len);
}

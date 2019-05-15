/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_applier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:35:08 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/08 11:55:36 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		format_caller(t_struct_tab struct_tab, va_list ap,\
		char **result, t_stack *stack)
{
	int				i;
	int				len_arg;

	i = -1;
	len_arg = 0;
	while (++i < 5)
	{
		if (stack->format && ft_strchr(struct_tab.call_format[i].format,\
					stack->format))
		{
			if ((len_arg = struct_tab.call_format[i].f(ap, stack,\
							result)) == -1)
				return (-1);
			break ;
		}
	}
	if (i == 5 && stack->format)
	{
		if (!(*result = (char*)ft_memalloc(2)))
			return (-1);
		**result = stack->format;
		len_arg = 1;
	}
	return (len_arg);
}

static int		attributs_caller(char **result, t_struct_tab struct_tab,\
		t_stack *stack, int len_arg)
{
	int			i;
	int			j;

	i = -1;
	while (stack->attributs && (stack->attributs)[++i])
	{
		j = -1;
		while (++j < 3)
			if (struct_tab.call_attr[j].attr == (stack->attributs)[i])
			{
				if ((len_arg = struct_tab.call_attr[j].f(result,\
								stack, len_arg)) == -1)
					return (-1);
				break ;
			}
	}
	return (len_arg);
}

int				ft_stack_applier(t_stack *stack, t_struct_tab struct_tab,\
		va_list ap, int *len)
{
	char	*result;
	int		len_arg;

	result = NULL;
	if ((len_arg = format_caller(struct_tab, ap, &result,\
					stack)) == -1)
		return (-1);
	if (!result)
		return (*len);
	if ((len_arg = attributs_caller(&result, struct_tab,\
					stack, len_arg)) == -1)
		return (-1);
	if ((len_arg = ft_width(&result, stack, len_arg)) == -1)
		return (-1);
	concat_buff(&struct_tab.buff, result, len_arg, len);
	ft_strdel(&result);
	return (*len);
}

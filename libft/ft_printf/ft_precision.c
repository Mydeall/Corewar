/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:26:35 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/14 14:16:50 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*str_precision(char *result, int precision)
{
	char	*tmp;

	if (result && precision != -1 && (int)ft_strlen(result) > precision)
	{
		tmp = result;
		result = ft_strsub(result, 0, precision);
		ft_strdel(&tmp);
	}
	return (result);
}

static char	*int_precision(char *result, int i, int precision)
{
	char	*str;
	char	*tmp;

	if (result && (int)ft_strlen(&result[i]) < precision)
	{
		if (!(str = (char*)ft_memalloc(precision - ft_strlen(result) + 1)))
			return (NULL);
		ft_memset(str, '0', precision - ft_strlen(result));
		tmp = result;
		if (!(result = ft_strjoin(str, result)))
			return (NULL);
		ft_strdel(&tmp);
		ft_strdel(&str);
	}
	else if (result && precision == 0 && !(ft_strcmp(result, "0")))
	{
		tmp = result;
		result = ft_strnew(1);
		ft_strdel(&tmp);
	}
	return (result);
}

char		*precision(char *result, t_stack *stack)
{
	char	*sub;
	char	*tmp;
	int		i;

	if (result && ft_strchr("diouxXpb", stack->format))
	{
		i = 0;
		if (ft_strcmp(result, "0"))
			while (result && result[i] && ft_strchr("0xXb+- ", result[i]))
				i++;
		if (!(sub = ft_strsub(result, 0, i)))
			return (NULL);
		tmp = result;
		result = ft_strdup(&result[i]);
		ft_strdel(&tmp);
		result = int_precision(result, i, stack->precision);
		tmp = result;
		result = ft_strjoin(sub, result);
		ft_strdel(&tmp);
		ft_strdel(&sub);
		return (result);
	}
	else if (stack->format == 's')
		return (str_precision(result, stack->precision));
	return (result);
}

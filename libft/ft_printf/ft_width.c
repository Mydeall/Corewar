/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:11:42 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/14 13:43:45 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*digit_zero(char **result, char *strz)
{
	char	*tmp;
	char	*sub;
	int		i;

	i = 0;
	while ((ft_strchr("0xXb+- ", (*result)[i])) && (*result)[i] != 0)
		i++;
	if (!(sub = ft_strsub(*result, 0, i)))
		return (NULL);
	*result = &(*result)[i];
	tmp = strz;
	strz = ft_strjoin(sub, strz);
	ft_strdel(&tmp);
	ft_strdel(&sub);
	return (strz);
}

static int	ft_zero(char **result, t_stack *stack, int len_arg)
{
	char *strz;
	char *tmp;

	if (!(strz = (char*)ft_memalloc(stack->width - len_arg + 1)))
		return (-1);
	ft_memset(strz, '0', stack->width - len_arg);
	tmp = *result;
	if (ft_strchr("diouxXpfb", stack->format))
		if (!(strz = digit_zero(result, strz)))
			return (-1);
	if (!(*result = ft_strjoin(strz, *result)))
		return (-1);
	ft_strdel(&tmp);
	ft_strdel(&strz);
	len_arg += stack->width - len_arg;
	return (len_arg);
}

static char	*concat_str(char *result, char *str, t_stack *stack, int len_arg)
{
	int		i;
	int		str_pos;
	char	*tmp;

	i = -1;
	str_pos = stack->width - len_arg;
	if (stack->attributs && ft_strchr(stack->attributs, '-'))
		str_pos = 0;
	while (++i < len_arg)
		str[i + str_pos] = result[i];
	tmp = result;
	result = str;
	ft_strdel(&tmp);
	return (result);
}

int			ft_width(char **result, t_stack *stack, int len_arg)
{
	char	*str;

	if (len_arg < stack->width)
	{
		if (stack->attributs && ft_strchr(stack->attributs, '1')
				&& (stack->precision == -1
				|| !ft_strchr("diouxXpbf", stack->format))
				&& !ft_strchr(stack->attributs, '-'))
			return (ft_zero(result, stack, len_arg));
		if (!(str = (char*)ft_memalloc(stack->width + 1)))
			return (-1);
		ft_memset(str, ' ', stack->width);
		*result = concat_str(*result, str, stack, len_arg);
		if (!(*result))
			return (-1);
		len_arg += stack->width - len_arg;
	}
	return (len_arg);
}

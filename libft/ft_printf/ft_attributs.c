/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attributs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:51:37 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/14 13:44:02 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hashtag_application(char **result, t_stack *stack, int len_arg)
{
	if ((stack->format == 'o' && *result[0] != '0') || stack->format == 'b')
	{
		if (stack->format == 'o')
			*result = ft_strjoin("0", *result);
		len_arg += 1;
	}
	else if (stack->format == 'x' || stack->format == 'X')
	{
		if (stack->format == 'x')
			*result = ft_strjoin("0x", *result);
		else if (stack->format == 'b')
			*result = ft_strjoin("0b", *result);
		else if (stack->format == 'X')
			*result = ft_strjoin("0X", *result);
		len_arg += 2;
	}
	return (len_arg);
}

int			ft_hashtag(char **result, t_stack *stack, int len_arg)
{
	char	*tmp;
	int		verif;

	if (!(ft_strchr("oxXfb", stack->format)))
		return (len_arg);
	tmp = *result;
	if (stack->format == 'f' && stack->precision == 0)
		*result = ft_strjoin(*result, ".");
	else if (stack->format != 'f')
	{
		verif = 0;
		while ((*result)[verif] == '0')
			verif++;
		if (verif == len_arg && !(stack->precision == 1 && len_arg == 0
					&& stack->format == 'o'))
			return (len_arg);
		len_arg = hashtag_application(result, stack, len_arg);
	}
	if (tmp != *result)
		ft_strdel(&tmp);
	return (len_arg);
}

int			ft_plus(char **result, t_stack *stack, int len_arg)
{
	char *tmp;

	if (ft_strchr("dif", stack->format))
	{
		if (!ft_strchr(*result, '-'))
		{
			tmp = *result;
			*result = ft_strjoin("+", *result);
			len_arg += 1;
			ft_strdel(&tmp);
		}
	}
	return (len_arg);
}

int			ft_space(char **result, t_stack *stack, int len_arg)
{
	char *tmp;

	if (ft_strchr("dif", stack->format) && !ft_strchr(stack->attributs, '+'))
	{
		if (!ft_strchr(*result, '-'))
		{
			tmp = *result;
			*result = ft_strjoin(" ", *result);
			len_arg += 1;
			ft_strdel(&tmp);
		}
	}
	return (len_arg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:33:41 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/14 14:18:33 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_format(va_list ap, t_stack *stack, char **result)
{
	char			*tmp;
	t_ulli			arg;
	long long int	cpy;
	t_ulli			ucpy;

	arg = va_arg(ap, t_ulli);
	if (stack->format == 'd' || stack->format == 'i')
	{
		cpy = int_modifier(arg, stack);
		*result = ft_itoa(cpy);
	}
	else
	{
		ucpy = unsigned_modifier(arg, stack);
		*result = unsigned_conversion(ucpy, stack);
	}
	if (stack->precision != -1)
		*result = precision(*result, stack);
	if (stack->format == 'p')
	{
		tmp = *result;
		*result = ft_strjoin("0x", *result);
		ft_strdel(&tmp);
	}
	return (ft_strlen(*result));
}

int	str_format(va_list ap, t_stack *stack, char **result)
{
	char *arg;

	arg = va_arg(ap, char*);
	if (!(arg) && stack->precision != -1)
		*result = ft_memalloc(1);
	else if (arg && !(*result = ft_strdup(arg)))
		return (-1);
	if (stack->precision != -1)
		*result = precision(*result, stack);
	else if (!(*result))
		*result = ft_strdup("(null)");
	if (!*result)
		return (-1);
	return ((int)ft_strlen(*result));
}

int	char_format(va_list ap, t_stack *stack, char **result)
{
	int		arg;

	(void)stack;
	if (!(*result = (char*)ft_memalloc(2)))
		return (-1);
	arg = va_arg(ap, int);
	**result = (char)arg;
	return (1);
}

int	double_format(va_list ap, t_stack *stack, char **result)
{
	long double arg;

	if (stack->modifier && !ft_strcmp("L", stack->modifier))
		arg = va_arg(ap, long double);
	else
		arg = va_arg(ap, double);
	if (stack->precision == -1)
		stack->precision = 6;
	if (!(*result = ft_dtoa(arg, stack->precision)))
		return (-1);
	return (ft_strlen(*result));
}

int	percent_format(va_list ap, t_stack *stack, char **result)
{
	(void)ap;
	(void)stack;
	if (!(*result = (char*)ft_memalloc(2)))
		return (-1);
	**result = '%';
	return (1);
}

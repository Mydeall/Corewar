/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:13:55 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/21 13:15:42 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int	int_modifier(t_ulli arg, t_stack *stack)
{
	if (!(stack->modifier))
		return ((int)arg);
	else if (ft_strcmp("hh", stack->modifier) == 0)
		return ((char)arg);
	else if (ft_strcmp("h", stack->modifier) == 0)
		return ((short int)arg);
	else if (ft_strcmp("l", stack->modifier) == 0)
		return ((long int)arg);
	else if (ft_strcmp("ll", stack->modifier) == 0)
		return ((long long int)arg);
	return ((int)arg);
}

t_ulli			unsigned_modifier(t_ulli arg, t_stack *stack)
{
	if (stack->format == 'p')
		return (arg);
	else if (!(stack->modifier))
		return ((unsigned int)arg);
	else if (ft_strcmp("hh", stack->modifier) == 0)
		return ((unsigned char)arg);
	else if (ft_strcmp("h", stack->modifier) == 0)
		return ((unsigned short int)arg);
	else if (ft_strcmp("l", stack->modifier) == 0)
		return ((unsigned long int)arg);
	else if (ft_strcmp("ll", stack->modifier) == 0)
		return ((unsigned long long int)arg);
	return ((unsigned int)arg);
}

long double		f_modifier(long double arg, t_stack *stack)
{
	if (stack->modifier && ft_strcmp("L", stack->modifier))
		return ((double)arg);
	return (arg);
}

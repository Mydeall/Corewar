/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:19:16 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/21 13:16:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*unsigned_conversion(t_ulli arg, t_stack *stack)
{
	if (stack->format == 'o')
		return (ft_itoa_base(arg, "01234567"));
	else if (stack->format == 'X')
		return (ft_itoa_base(arg, "0123456789ABCDEF"));
	else if (stack->format == 'x' || stack->format == 'p')
		return (ft_itoa_base(arg, "0123456789abcdef"));
	else if (stack->format == 'b')
		return (ft_itoa_base(arg, "01"));
	return (ft_itoa_base(arg, "0123456789"));
}

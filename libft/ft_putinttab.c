/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putinttab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:13:35 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/16 12:36:35 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putinttab(int *tab, size_t size)
{
	if (!(tab))
	{
		ft_putendl("(null)");
		return ;
	}
	ft_putchar('{');
	while ((--size + 1) > 0)
	{
		ft_putnbr(*tab);
		if (size != 0)
			ft_putstr(", ");
		tab++;
	}
	ft_putstr("}\n");
}

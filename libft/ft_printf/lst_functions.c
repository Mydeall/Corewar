/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:04:39 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/21 12:14:49 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	node_reset(t_stack *lst)
{
	lst->attributs = NULL;
	lst->modifier = NULL;
	lst->width = 0;
	lst->precision = -1;
	lst->format = 0;
}

void	free_node(t_stack *lst)
{
	if (lst->attributs)
		ft_strdel(&lst->attributs);
	if (lst->modifier)
		ft_strdel(&lst->modifier);
}

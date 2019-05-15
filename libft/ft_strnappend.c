/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnappend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:24:22 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 16:29:35 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnappend(char **str, char *ext, int n)
{
	int	i;
	int	j;

	if (!n)
		return (0);
	if (!*str)
	{
		if (!(*str = (char*)ft_strnew(n + 1)))
			return (1);
		ft_strncat(*str, ext, n);
		return (0);
	}
	i = ft_strlen(*str);
	if (!(*str = (char*)realloc((void*)(*str),\
					sizeof(char) * (i + n + 1))))
		return (1);
	j = -1;
	while (++j < n)
		(*str)[++i - 1] = ext[j];
	(*str)[i] = 0;
	return (0);
}

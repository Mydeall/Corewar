/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:23:59 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/13 17:34:12 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjointab(const char **tab, const char *join)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	if (!(tab))
		return (NULL);
	while (tab[++i - 1])
	{
		len += ft_strlen(tab[i - 1]);
		if (tab[i])
			len += ft_strlen(join);
	}
	if (!(str = ft_strnew(len + 1)))
		return (NULL);
	i = 0;
	while (tab[++i - 1])
	{
		if (i == 1)
			str = ft_strcpy(str, *tab);
		else
			str = ft_strcat(str, ft_strjoin(join, tab[i - 1]));
	}
	return (str);
}

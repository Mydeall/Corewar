/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:05:48 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/07 14:44:40 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	verif_base(const char *base)
{
	size_t j;
	size_t i;

	i = -1;
	while (base[++i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		j = -1;
		while (base[++j] != '\0')
			if (base[i] == base[j] && i != j)
				return (1);
	}
	if (i < 2)
		return (1);
	return (0);
}

static int	size_result(unsigned long long int nb, int len_b)
{
	int len;

	len = 0;
	while (nb != 0)
	{
		nb = nb / len_b;
		len++;
	}
	return (len);
}

char		*ft_itoa_base(unsigned long long int nb, const char *base)
{
	size_t	len;
	int		len_b;
	char	*str;

	if (!(base) || verif_base(base))
		return (NULL);
	len_b = ft_strlen(base);
	len = size_result(nb, len_b);
	if (nb == 0)
		return (ft_strdup("0"));
	if (!(str = ft_strnew(len + 1)))
		return (NULL);
	while (nb != 0)
	{
		str[--len] = base[nb % len_b];
		nb = nb / len_b;
	}
	return (str);
}

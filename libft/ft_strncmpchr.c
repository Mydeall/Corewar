/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmpchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:25:05 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 16:29:35 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		strncmpchr(char *s1, char *s2, int n)
{
	int			i;
	static int	appel = 0;

	appel++;
	i = -1;
	while (++i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (i);
	}
	return (-1);
}

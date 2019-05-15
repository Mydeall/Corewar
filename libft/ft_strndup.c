/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:26:04 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/09 16:29:34 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, size_t n)
{
	size_t	i;
	char	*dup;

	if (!s1)
		return (NULL);
	if (!(dup = (char*)malloc(sizeof(char) * n + 1)))
		return (NULL);
	i = -1;
	while (++i < n)
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}

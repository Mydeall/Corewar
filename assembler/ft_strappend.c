/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:05:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/08 15:43:49 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_strappend(char **str, char *ext)
{
	int	i;
	int	j;

	if (!*str)
	{
		if (!(*str = ft_strdup(ext)))
			return (1);
		return (0);
	}
	i = ft_strlen(*str);
	if (!(*str = (char*)realloc((void*)(*str),\
					sizeof(char) * (i + ft_strlen(ext) + 1))))
		return (1);
	j = -1;
	while (ext[++j])
		(*str)[++i - 1] = ext[j];
	(*str)[i] = 0;
	return (0);
}

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

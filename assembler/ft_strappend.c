/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:05:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/25 18:20:20 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "libft.h"
*/
#include "asm.h"

int	ft_strappend(char **str, char *ext)
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

int	ft_strnappend(char **str, char *ext, int n)
{
	int	i;
	int	j;

	if (!n)
		return (0);
	if (!*str)
	{
		if (!(*str = ft_strdup(ext)))
			return (1);
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

int	strncmpchr(char *s1, char *s2, int n)
{
	int	i;
	static int	appel = 0;
	
	appel++;
	i = -1;
	while (++i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			printf("appel %d\n", appel);
			printf("i = %d\n", i);
			return (i);
		}
	}
	return (-1);
}

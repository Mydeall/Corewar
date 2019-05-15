/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinarg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 13:08:24 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/16 13:08:26 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	compute_size(int nb, va_list ap)
{
	va_list	ap_cpy;
	char	*str;
	int		len;
	int		i;

	va_copy(ap_cpy, ap);
	i = -1;
	len = 0;
	while (++i < nb)
	{
		str = va_arg(ap_cpy, char*);
		len += ft_strlen(str);
	}
	va_end(ap_cpy);
	return (len);
}

char		*ft_strjoinarg(int nb, ...)
{
	char	*str;
	char	*tmp;
	int		i;
	va_list	ap;
	int		len;

	va_start(ap, nb);
	len = compute_size(nb, ap);
	if (!len || !(str = ft_strnew(len + 1)))
		return (NULL);
	tmp = va_arg(ap, char*);
	if (tmp)
		str = ft_strcpy(str, tmp);
	i = -1;
	while (++i < nb - 1)
	{
		tmp = va_arg(ap, char*);
		if (tmp)
			str = ft_strcat((char*)str, tmp);
	}
	return (str);
}

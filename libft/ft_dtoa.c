/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:43:58 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/14 13:44:33 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <float.h>

static char			*get_bigger(char *result)
{
	char *tmp;

	tmp = result;
	result[0] = '0';
	result = ft_strjoin("1", result);
	ft_strdel(&tmp);
	return (result);
}

static char			*ft_global_round(char *result, long double nb, int i)
{
	int n;

	n = result[i] - '0';
	if ((nb * 10 > 5 && (result[i] - '0') < 10) || (nb * 10 == 5
				&& (result[i] - '0') % 2 == 1))
		n++;
	if (n < 10)
		result[i] = n + '0';
	else
	{
		while (n == 10 && i > 0)
		{
			result[i] = '0';
			if (result[--i] == '.')
				i--;
			n = (result[i] - '0' + 1);
		}
		if (i == 0 && n == 10)
			return (get_bigger(result));
		result[i] = n + '0';
	}
	return (result);
}

static void			conversion(char **result, long double n, int precision,\
		int count)
{
	int			i;
	long double pow;

	if (precision != -1 && precision < 20 && n < DBL_MAX && n > DBL_MIN)
		n = (double)n;
	i = -1;
	pow = 1;
	while ((n / pow) >= 1)
		pow *= 10;
	while ((pow /= 10) >= 0.1)
	{
		(*result)[++i] = (int)(n / pow) + '0';
		n = n - ((*result)[i] - '0') * pow;
	}
	if (precision != 0)
		(*result)[++i] = '.';
	while (n > 0 && (precision == -1 || (i + 1 - count) < precision))
	{
		n *= 10.0;
		(*result)[++i] = (int)(n) + '0';
		n = n - ((*result)[i] - '0');
	}
	*result = ft_global_round(*result, n, i);
}

static int			count_left(long double n)
{
	int			count;

	count = 1;
	while ((n /= 10) >= 1)
		count++;
	return (count);
}

char				*ft_dtoa(long double n, int precision)
{
	char		*result;
	int			sign;
	int			count;
	char		*tmp;

	sign = n < 0 ? 1 : 0;
	n = n < 0 ? -n : n;
	count = count_left(n);
	count = precision == 0 ? count : count + 1;
	if (!(result = (char*)ft_memalloc(count + precision + 1)))
		return (NULL);
	ft_memset(result, '0', count + precision);
	if (n == 0 && precision != 0)
		result[1] = '.';
	conversion(&result, n, precision, count);
	if (sign == 1)
	{
		tmp = result;
		result = ft_strjoin("-", result);
		ft_strdel(&tmp);
	}
	return (result);
}

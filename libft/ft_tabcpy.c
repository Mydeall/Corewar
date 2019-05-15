/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:48:33 by malluin           #+#    #+#             */
/*   Updated: 2018/11/26 18:55:50 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabcpy(char **src, char ***dest)
{
	int		i;

	i = 0;
	while (src[i])
	{
		(*dest)[i] = ft_strdup(src[i]);
		i++;
	}
	(*dest)[i] = 0;
}
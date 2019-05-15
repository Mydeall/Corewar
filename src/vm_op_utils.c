/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:20:14 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/09 17:08:40 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

int		*ft_decode_byte(t_vm *vm, unsigned char c, int *tab)
{
	tab[0] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[1] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[2] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[3] = vm->enc[(c >> 6)];
	return (tab);
}

void	ft_decode_byte2(t_vm *vm, unsigned char c)
{
	vm->enc_byte[0] = vm->enc[(c >> 6) & 3];
	vm->enc_byte[1] = vm->enc[(c >> 4) & 3];
	vm->enc_byte[2] = vm->enc[(c >> 2) & 3];
	vm->enc_byte[3] = vm->enc[c & 3];
	if (vm->debug == 1)
		ft_printf("##Encoding byte: || %02b %02b %02b %02b ||\n",
			vm->enc_byte[0], vm->enc_byte[1], vm->enc_byte[2], vm->enc_byte[3]);
}

void	ft_decode_byte_codes(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (vm->enc_byte[i] == IND_SIZE)
			vm->enc_byte_codes[i] = T_IND;
		else if (vm->enc_byte[i] == DIR_SIZE)
			vm->enc_byte_codes[i] = T_DIR;
		else if (vm->enc_byte[i] == T_REG)
			vm->enc_byte_codes[i] = T_REG;
		else
			vm->enc_byte_codes[i] = 0;
		i++;
	}
	if (vm->debug == 1)
		ft_printf("##Encoding byte codes: ||%b %b %b %b ||\n",
			vm->enc_byte_codes[0], vm->enc_byte_codes[1],
			vm->enc_byte_codes[2], vm->enc_byte_codes[3]);
}

int		is_register(int decoded_by, unsigned char arena_by)
{
	if (decoded_by != T_REG || arena_by > REG_NUMBER || arena_by <= 0)
		return (0);
	return (1);
}

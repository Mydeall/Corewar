/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/04/22 16:53:43 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_FUNC_H
# define OP_FUNC_H

int		(*op_func[16])(t_vm *vm, t_process *proc) = {
		op_live, op_load, op_store, op_add,
		op_sub, op_and, op_or, op_xor,
		op_zjmp, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL};

#endif

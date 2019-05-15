/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/05/03 10:29:51 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_FUNC_H
# define OP_FUNC_H

int		(*g_op_func[16])(t_vm *vm, t_process *proc) = {
	op_live, op_load, op_store, op_add,
	op_sub, op_and, op_or, op_xor,
	op_zjmp, op_ldi, op_sti, op_fork,
	op_lld, op_lldi, op_lfork, op_aff
};

#endif

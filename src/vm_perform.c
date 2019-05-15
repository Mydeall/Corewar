/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_perform.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:03 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 18:52:44 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "op_func.h"
#include "libft.h"

extern t_op g_op_tab[17];

void	read_op_code(t_vm *vm, t_process *proc)
{
	proc->next_op = vm->arena[verif(proc->pc)].by;
	if (proc->next_op >= 1 && proc->next_op <= 16)
		proc->wait_cycles = g_op_tab[proc->next_op - 1].cycles;
}

void	pc_forward_sequence(t_vm *vm, t_process *proc)
{
	int		i;

	vm->arena[proc->pc % MEM_SIZE].proc_id = 0;
	if ((vm->detail & 16) != 0)
	{
		ft_printf("ADV %d (%06p -> %06p) ", proc->step_over, proc->pc,
			((proc->pc + proc->step_over) % MEM_SIZE + MEM_SIZE) % MEM_SIZE);
		i = 0;
		while (i < proc->step_over)
			ft_printf("%02x ", vm->arena[((i++) + proc->pc % MEM_SIZE
			+ MEM_SIZE) % MEM_SIZE].by);
		ft_printf("\n");
	}
	proc->pc = ((proc->pc + proc->step_over) % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
	vm->arena[proc->pc % MEM_SIZE].proc_id = 1;
	proc->step_over = 0;
}

void	pc_jump(t_vm *vm, t_process *proc)
{
	vm->arena[proc->pc % MEM_SIZE].proc_id = 0;
	proc->pc = ((proc->pc + proc->step_over) % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
	vm->arena[proc->pc % MEM_SIZE].proc_id = 1;
	proc->step_over = 0;
}

void	pc_forward_one(t_vm *vm, t_process *proc)
{
	vm->arena[proc->pc % MEM_SIZE].proc_id = 0;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	vm->arena[proc->pc % MEM_SIZE].proc_id = 1;
}

void	perform_op(t_vm *vm, t_process *proc)
{
	int		res;

	res = 0;
	if (proc->next_op >= 1 && proc->next_op <= 16
			&& g_op_func[proc->next_op - 1] != NULL)
	{
		if (check_args(vm, proc, proc->next_op - 1, 2) == 1)
		{
			if ((vm->detail & 4) != 0 && proc->next_op != 16)
				ft_printf("P %4d | %s", ft_iabs(proc->id_proc)
					, g_op_tab[proc->next_op - 1].op_name);
			res = g_op_func[proc->next_op - 1](vm, proc);
			if (res == 1)
				pc_forward_sequence(vm, proc);
			else if (res == 2)
				pc_jump(vm, proc);
			else
				pc_forward_one(vm, proc);
		}
		else
			pc_forward_sequence(vm, proc);
	}
	else
		pc_forward_one(vm, proc);
}

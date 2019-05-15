/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:39:59 by malluin           #+#    #+#             */
/*   Updated: 2019/05/14 16:26:08 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include <time.h>
# include <ncurses.h>

# define MAGIC_SIZE	4
# define NAME_SIZE	128
# define PAD_SIZE	4
# define BOT_SIZE	4
# define COMMENT_SIZE	2048

# define R_W 52
# define L_W 198
# define L_H 68
# define T_WIN WINDOW

# define FLUO_YELLOW 100
# define FLUO_GREEN 101
# define FLUO_BLUE 102
# define FLUO_RED 103

typedef struct			s_process {
	unsigned char		regs[REG_NUMBER][REG_SIZE];
	int					pc;
	char				carry;
	int					wait_cycles;
	int					last_live;
	int					step_over;
	int					id_parent;
	long				id_proc;
	unsigned char		next_op;
	struct s_process	*next;
}						t_process;

typedef struct			s_time {
	clock_t				begin;
	clock_t				current;
	clock_t				pause;
}						t_time;

typedef struct			s_player {
	t_header			*header;
	int					code_start;
	char				*file_path;
	int					player_number;
	int					order_arg;
	int					nb_process;
	int					lives_curr;
}						t_player;

typedef	struct			s_case {
	int					id;
	int					proc_id;
	unsigned char		by;
	int					st_id;
}						t_case;

typedef struct			s_visu {
	short				w_l;
	short				w_r;
	short				h;
	short				b_w_l;
	short				b_w_r;
	short				b_h;
	WINDOW				*boite_l;
	WINDOW				*boite_r;
}						t_visu;

typedef struct			s_vm {
	t_player			*players[MAX_PLAYERS];
	t_process			*process;
	t_case				arena[MEM_SIZE];
	t_visu				visu;
	int					cycles;
	int					players_alive;
	int					cycle_to_die;
	int					nb_process;
	int					stop;
	int					cycle_sec;
	int					last_player_live;
	int					dump_cycle;
	int					nb_players;
	char				ncurses;
	int					enc[4];
	int					enc_byte[4];
	int					enc_byte_codes[4];
	char				current_checks;
	int					number_of_live;
	char				debug;
	char				detail;
	int					ac;
}						t_vm;

typedef struct			s_op {
	char				*op_name;
	int					nb_args;
	int					args_size[3];
	int					op_num;
	int					cycles;
	char				*op_desc;
	int					encoding;
	int					size_direct;
}						t_op;

/*
** Ncurses
*/

void					refresh_window(t_vm *vm, int run);
void					initialize_window(t_vm *vm);
void					initialize_color(void);
void					close_window(t_vm *vm);
int						count_players(t_vm *vm);

/*
** Init structures
*/

void					initialize_vm(t_vm *vm, int ac);
void					add_player(t_vm *vm, char *path, int next_nb, int i);

/*
** Parsing
*/

void					ft_parse_args(t_vm *vm, int ac, char **av, int i);
void					vm_read_byte(t_player *player, t_vm *vm);

/*
** Init and utils for processes
*/

t_process				*new_process(int id_parent, int pc);
void					add_first_process_front(t_vm *vm, t_player *player,
						t_process **blist);
void					create_processes(t_vm *vm);
int						read_reg(unsigned char *str);
void					assign_reg(t_process *process, short reg, int value);
void					add_child_process(t_vm *vm, t_process *parent,
						int child_pc);
void					remove_dead_process(t_vm *vm);

/*
** Main loop
*/

void					main_loop(t_vm *vm);
int						check_args(t_vm *vm, t_process *proc,
						int op_code, int size);
void					perform_op(t_vm *vm, t_process *proc);
void					read_op_code(t_vm *vm, t_process *proc);
void					reset_lives(t_vm *vm);
int						time_mgt(t_vm *vm, t_time *time, int cycles);

/*
** Print
*/

void					print_intro(t_vm *vm);
void					dump_memory(t_vm *vm);
int						*ft_decode_byte(t_vm *vm, unsigned char c, int *tab);
void					ft_decode_byte2(t_vm *vm, unsigned char c);
void					ft_decode_byte_codes(t_vm *vm);
int						is_register(int decoded_by, unsigned char arena_by);

/*
** Operations
*/

int						op_live(t_vm *vm, t_process *proc);
int						op_load(t_vm *vm, t_process *proc);
int						op_store(t_vm *vm, t_process *p);
int						op_add(t_vm *vm, t_process *proc);
int						op_sub(t_vm *vm, t_process *proc);
int						op_and(t_vm *vm, t_process *proc);
int						op_or(t_vm *vm, t_process *proc);
int						op_xor(t_vm *vm, t_process *proc);
int						op_zjmp(t_vm *vm, t_process *p);
int						op_fork(t_vm *vm, t_process *proc);
int						op_lld(t_vm *vm, t_process *p);
int						op_lldi(t_vm *vm, t_process *p);
int						op_lfork(t_vm *vm, t_process *proc);
int						op_aff(t_vm *vm, t_process *proc);
int						op_ldi(t_vm *vm, t_process *p);
int						op_sti(t_vm *vm, t_process *p);
void					reg_to_reg(int src_reg, int dst_reg, t_process *p);
void					reg_to_mem(t_vm *vm, t_process *p, int reg, int pos);
void					mem_to_reg(int reg, int pos, t_vm *vm, t_process *p);
int						read_arena(t_vm *vm, int pos, int size);
void					end_game(t_vm *vm);
void					free_structs(t_vm *vm);
int						op_load_utils(t_vm *vm, t_process *p, int res, int r);
int						op_ldi_utils(t_vm *vm, t_process *p, int k, int size);
int						op_lldi_utils(t_vm *vm, t_process *p, int k, int size);
int						*read_args(t_vm *vm, t_process *proc, int *size,
						int nb_args);
int						verif(int nb);

/*
** Debug
*/

void					ft_print_players(t_vm *vm);
void					ft_print_xstr(int size, char *str, int wid);
void					ft_print_xarena(t_vm *vm, int wid);
void					increment_memory(t_vm *vm);
void					ft_print_process(t_vm *vm);

/*
** Errors
*/

void					ft_usage(void);
void					ft_error_read(t_vm *vm, char *str);
void					ft_error_too_many(t_vm *vm);
void					ft_incorrect_number(t_vm *vm);
void					ft_error_already_assigned(t_vm *vm);
void					error_champ_too_big(t_vm *vm);
void					error_champ_too_small(t_vm *vm);
void					error_read(t_vm *vm);
void					error_wrong_header(t_vm *vm);
void					error_wrong_weight(t_vm *vm);

#endif

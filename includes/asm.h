/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:09:56 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/02 16:22:40 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H__
# define __ASM_H__

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

# define BUFF_SIZE_ASM 2048 
# define BUFF_SIZE_W 2048

typedef enum		e_lex
{
	NAME = 4,
	COMMENT = 5,
	CARRIAGE = 6,
	COMMA = 7,
	DIRECT = 13,
	INDIRECT = 19,
	LABEL = 22,
	OPCODE = 23,
	REGISTER = 25,
	NONE = 0
}					t_lex;

typedef struct		s_token
{
	t_lex			lexem;
	char			*value;
	int				line;
	int				col;
	int				size;
	int				address;
	struct s_token	*next;
}					t_token;

typedef struct		s_reader
{
	char			buff[BUFF_SIZE_ASM + 1];
	int				line;
	int				col;
	int				cursor;
	int				state;
	int				nb_chars;
	char			*rest;
}					t_reader;

typedef struct		s_writer
{
	char			buff[BUFF_SIZE_W];
	size_t			cursor;
	char			*output;
	size_t			address;
}					t_writer;

typedef struct		s_instr
{
	int				opcode;
	char			*label;
	t_token			*params;
	struct s_instr	*next;
}					t_instr;

typedef struct		s_oper
{
	char	*inst;
	int		opcode;
	int		enc_byte;
	int		dir_size;
}					t_oper;

extern t_oper g_op_tab[16];
extern char	*(g_instructions[16]);
extern char	*g_index_col_lex[12];
extern int g_automate_lex[27][13];
extern int g_automate_syn[47][9];
extern t_lex g_index_col_syn[9];
extern t_lex g_index_col_syn[9];

int			write_output(t_writer *writer, char *file_name);
int			scanner_asm(int fd, t_token **tokens, t_token **labels);

int	create_value(t_token *token, t_reader *reader);

void	free_manager(t_token *tokens, t_instr *instructions, t_token *labels);
void	free_tokens(t_token **tokens);
void	free_token(t_token **token);

int		complete_token(t_token *token, int state, t_reader *reader);
int		create_token(t_token **token, t_reader *reader, int start);
int		append_token(t_token **tokens, t_token *token, int state, t_reader *reader);
int		append_label(t_token *token, t_token **labels);
t_token	*get_back_token(t_token **tokens);

int		parser_asm(t_token **tokens, t_instr **instructions, t_token *labels);

int		print_arg_error(int	error_id);
int		print_sys_error(int errnum);
int		print_lex_error(int line, int col);
int		print_syn_error(t_token *token, int state);
int		print_len_error(t_token *token, int max);
int		print_label_error(t_token *token, t_token *dup);
int		print_int_error(t_token *token, int min, int max);

int	strncmpchr(char *s1, char *s2, int n);
int	ft_strnappend(char **str, char *ext, int n);
int	ft_strappend(char **str, char *ext);

void		check_tokens(t_token *tokens);
void		check_instructions(t_instr *instructions);
void		print_lexem(t_lex lexem);
void		print_token(t_token *token);

void		insert_value(char *str, unsigned int value, int size);
int			write_into_buffer(t_writer *writer, unsigned int nb, size_t size);
int			write_text(t_writer *writer, char *text, size_t len);
int			concat_output(t_writer *writer);

int		encoder_asm(t_instr *instructions, t_token *labels, char *file_name);
void	replace_label_value(t_writer *writer, t_token *labels, t_token *queue);
int		give_size_param(int opcode, t_lex lexem);
void	complete_labels(t_writer *writer, char *label, t_token *labels);

int		append_queue(t_token **queue, t_token *token);
int		ft_power(int nb, int pow);
#endif

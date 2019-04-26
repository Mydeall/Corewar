/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:09:56 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/26 18:26:29 by rkirszba         ###   ########.fr       */
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

# define BUFF_SIZE_ASM 1

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
	struct s_token	*next;
}					t_token;

typedef struct		s_instr
{
	int				opcode;
	char			*label;
	t_token			*params;
	struct s_instr	*next;
}					t_instr;

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

typedef struct		s_label
{
	char			*name;
	int				address;
	struct s_label	*next;
}					t_label;

extern char	*(g_instructions[16]);
extern char	*g_index_col_lex[12];
extern int g_automate_lex[27][13];
extern int g_automate_syn[47][9];
extern t_lex g_index_col_syn[9];

int			scanner_asm(int fd, t_token **tokens);

int	create_value(t_token *token, t_reader *reader);

void	free_manager(t_token *tokens, t_instr *instructions);
int		complete_token(t_token *token, int state, t_reader *reader);
void	free_token(t_token **token);
int		create_token(t_token **token, t_reader *reader, int start);
int		append_token(t_token **tokens, t_token *token, int state, t_reader *reader);
t_token	*get_back_token(t_token **tokens);

int		print_lex_error(int line, int col);
int		print_arg_error(int	error_id);
int		print_system_error(int errnum);

int	strncmpchr(char *s1, char *s2, int n);
int	ft_strnappend(char **str, char *ext, int n);
int	ft_strappend(char **str, char *ext);

#endif

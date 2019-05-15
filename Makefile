# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malluin <malluin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 14:56:26 by malluin           #+#    #+#              #
#    Updated: 2019/05/14 16:47:41 by malluin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_VM = corewar
NAME_ASM = asm

LIB_PATH = ./libft

SRC_VM_NAME =	op.c \
				vm_main.c \
				vm_core.c \
				vm_ncurses_win.c \
				vm_ncurses_refresh.c \
				vm_structs_initialize.c \
				vm_errors_messages.c \
				vm_errors_messages_2.c \
				vm_args_parsing.c \
				vm_debug.c \
				vm_read_byte.c \
				vm_process_mgmt.c	vm_process_mgmt_2.c\
				vm_utils.c \
				vm_print.c \
				vm_op_utils.c		vm_op_utils_2.c \
				vm_op_others.c \
				vm_op_arithmetic.c	vm_op_arithmetic_2.c \
				vm_op_load.c		vm_op_load_utils.c \
				vm_op_st_jmp.c \
				vm_end.c \
				vm_perform.c

SRC_ASM_NAME = 	asm_create_value.c\
				asm_scanner.c\
			   	asm_scanner_functions.c\
			   	asm_assembler.c\
				asm_error_manager.c\
			   	asm_error_value_manager.c\
			   	asm_globales.c\
			   	asm_parser.c\
				asm_parser_functions.c\
				asm_tokens_functions.c\
				asm_tokens_functions_scanner.c\
				asm_display.c\
				asm_free_functions.c\
				asm_encoder.c\
				asm_encoder_functions.c\
				asm_writer.c

HEADER_PATH = includes/
HEADER_NAME = op.h

SRC_PATH = src
OBJ_PATH = obj

CC = gcc
CCFLAGS =   -Wall -Wextra -Werror

CPPFLAGS = -I $(HEADER_PATH) -MMD
LIBFLAGS = -L $(LIB_PATH) -lft -lncurses

HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

OBJ_VM_NAME = $(SRC_VM_NAME:.c=.o)
SRC_VM = $(addprefix $(SRC_PATH)/,$(SRC_VM_NAME))
OBJ_VM = $(addprefix $(OBJ_PATH)/,$(OBJ_VM_NAME))

OBJ_ASM_NAME = $(SRC_ASM_NAME:.c=.o)
SRC_ASM = $(addprefix $(SRC_PATH)/,$(SRC_ASM_NAME))
OBJ_ASM = $(addprefix $(OBJ_PATH)/,$(OBJ_ASM_NAME))

all: lib $(NAME_VM) $(NAME_ASM)

lib:
	@make -C libft/

$(NAME_VM): $(OBJ_VM)
	@make -C libft/
	$(CC) $(CCFLAGS) $(LIBFLAGS) $^ -o $@

$(NAME_ASM): $(OBJ_ASM)
	@make -C libft/
	$(CC) $(CCFLAGS) $(LIBFLAGS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

clean:
	@make clean -C libft/
	rm -f $(OBJ_VM) $(OBJ_VM:.o=.d)
	rm -f $(OBJ_ASM) $(OBJ_ASM:.o=.d)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:	clean
	@make fclean -C libft/
	@rm -f $(NAME_VM)
	@rm -f $(NAME_ASM)

re: fclean
	$(MAKE) all

norme:
	norminette $(SRC_VM)
	norminette $(SRC_ASM)
	norminette $(INCLUDES)

.PHONY: lib make clean fclean re

-include $(OBJ_VM:.o=.d)
-include $(OBJ_ASM:.o=.d)

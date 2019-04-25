# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malluin <malluin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 14:56:26 by malluin           #+#    #+#              #
#    Updated: 2019/04/22 13:52:07 by fnussbau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_VM = corewar
NAME_ASM = asm

SRC_VM_NAME =		op.c \
					vm_main.c \
					vm_core.c \
					vm_ncurses_win.c \
					vm_ncurses_refresh.c \
					vm_structs_initialize.c \
					vm_errors_messages.c \
					vm_args_parsing.c \
					vm_debug.c \
					vm_read_byte.c \
					vm_process_mgmt.c \
					vm_utils.c \
					vm_print.c \
					vm_op_utils.c \
					vm_op_lst.c \
					vm_op_utils.c \
					vm_op_lst.c \
					vm_op_1.c

SRC_ASM_NAME = 	op.c \
					asm_main.c

HEADER_NAME = op.h

SRC_PATH = src
OBJ_PATH = obj
HEADER_PATH = includes/

CC = gcc -fsanitize=address -g
CCFLAGS =   -Wall -Wextra  #-Werror

CPPFLAGS = -I ./libftprintf/includes -I ./libftprintf/libft/includes -I $(HEADER_PATH) -MMD
LIBFLAGS = -L ./libftprintf/ -lftprintf -lncurses

# SDLFLAGS =  $(SDLINCL) -L/Users/malluin/.brew/Cellar/sdl2/2.0.9/lib -lSDL2 -L/Users/malluin/.brew/Cellar/SDL2_image/2.0.4/lib -lSDL2
# SDLINCL = -I /Users/malluin/.brew/Cellar/sdl2/2.0.9/include -I /Users/malluin/.brew/Cellar/SDL2_image/2.0.4/include

HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

OBJ_VM_NAME = $(SRC_VM_NAME:.c=.o)
SRC_VM = $(addprefix $(SRC_PATH)/,$(SRC_VM_NAME))
OBJ_VM = $(addprefix $(OBJ_PATH)/,$(OBJ_VM_NAME))

OBJ_ASM_NAME = $(SRC_ASM_NAME:.c=.o)
SRC_ASM = $(addprefix $(SRC_PATH)/,$(SRC_ASM_NAME))
OBJ_ASM = $(addprefix $(OBJ_PATH)/,$(OBJ_ASM_NAME))


all: $(NAME_VM) $(NAME_ASM)

$(NAME_VM): $(OBJ_VM)
	@make -C libftprintf/
	$(CC) $(CCFLAGS) $(LIBFLAGS) $^ -o $@

$(NAME_ASM): $(OBJ_ASM)
	@make -C libftprintf/
	$(CC) $(CCFLAGS) $(LIBFLAGS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

clean:
	@make clean -C libftprintf/
	rm -f $(OBJ_VM) $(OBJ_VM:.o=.d)
	rm -f $(OBJ_ASM) $(OBJ_ASM:.o=.d)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:	clean
	@make fclean -C libftprintf/
	@rm -f $(NAME_VM)
	@rm -f $(NAME_ASM)

re: fclean
	$(MAKE) all
#
# visu:
# 	gcc $(SRC2_NAME) $(SDLFLAGS) $(CPPFLAGS) $(LIBFLAGS) -o visualizer/$(NAME2)
#
# revisu:
# 	rm -f $(SRC2_NAME:.c=.o)
# 	rm -f $(SRC2_NAME:.c=.d)
# 	make visu
norme:
	norminette $(SRC_VM)
	norminette $(SRC_ASM)
	norminette $(INCLUDES)

.PHONY: make clean fclean re

-include $(OBJ_VM_NAME:.o=.d)
-include $(OBJ_ASM_NAME:.o=.d)

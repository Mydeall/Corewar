# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 15:43:12 by ccepre            #+#    #+#              #
#    Updated: 2019/05/01 14:55:09 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FLAGS = -Wall -Wextra -Werror

LIB_PATH = ./other
SRC_PATH = ./
VIS_PATH = ./visualizer
INC_PATH = ../includes

SRC_NAME = create_value.c\
		   ft_strappend.c\
		   scanner.c\
		   assembler.c\
		   error_manager.c\
		   globales.c\
		   parser.c\
		   tokens_functions.c\
		   display.c\
		   free_functions.c\
		   encoder.c\
		   encoder_functions.c\
		   writer.c

INC_NAME = asm.h \
		   get_next_line.h \
		   ft_printf.h \
		   libft.h

LIB_NAME = libft.a

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
#INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))

OBJ_SRC= $(SRC:.c=.o)

all : $(NAME)

%.o : %.c 
	@gcc $(FLAGS) -c $< -o $@ -I $(INC_PATH)

$(NAME) : $(OBJ_SRC) $(LIB)
	@gcc -o $(NAME) $(OBJ_SRC) $(LIB) -I $(INC_PATH)

clean :
	rm -f $(OBJ_SRC)

fclean : clean
	rm -f $(NAME)

re : fclean all

san : $(OBJ_SRC) $(LIB)
	gcc -g3 -fsanitize=address -o $(NAME) $(OBJ_SRC) $(LIB) -I $(INC_PATH)

.PHONY : san lib clean fclean re

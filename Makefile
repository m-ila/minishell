# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 21:41:34 by mbruyant          #+#    #+#              #
#    Updated: 2024/01/10 11:21:54 by mbruyant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

SRC = env/env_tab.c \
free/free_cmd_struct.c \
init/fill_tokens.c \
init/init_loop.c \
init/init_env_struct.c \
init/init_cmd_struct.c \
loop/main.c \
parsing/parse_user_input.c \
parsing/token_parse.c \
parsing/print_error.c \
parsing/tmp.c \
parsing/tmp2.c \
signal/signal.c

CFLAGS	= -Wextra -Wall -Werror -MMD -g3 -O2

CC = cc

INC = includes/minishell.h

OBJ_DIR = ./objs/

OBJ = $(SRC:.c=.o)

OBJ := $(addprefix $(OBJ_DIR), $(OBJ))

DEP := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline -include $(INC)

$(LIBFT) :
	make -C ./libft
clean:
	rm -rf $(OBJ_DIR)
	make fclean -C ./libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	${CC} ${CFLAGS} -c $< -o $@

-include $(DEP)
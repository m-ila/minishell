# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 21:41:34 by mbruyant          #+#    #+#              #
#    Updated: 2023/12/29 13:57:47 by mbruyant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

LIBFT = libft/libft.a

SRC = env/env_actual.c \
env/env_del.c \
env/env_display.c \
env/env_free.c \
env/env_init.c \
init/init_loop.c \
init/init_env_struct.c \
loop/main.c \
parsing/parse_user_input.c \
parsing/token_parse.c \
parsing/print_error.c

CFLAGS	= -Wextra -Wall -Werror -MMD -g3 -O2

CC = cc

INC = includes/

OBJ_DIR = ./objs/

OBJ = $(SRC:.c=.o)

OBJ := $(addprefix $(OBJ_DIR), $(OBJ))

DEP := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline -L $(INC)

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
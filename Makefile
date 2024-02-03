# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 21:41:34 by mbruyant          #+#    #+#              #
#    Updated: 2024/02/03 17:13:50 by mbruyant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

SRC = builtins/builtins.c \
builtins/ft_cd.c \
builtins/ft_echo.c \
builtins/ft_env.c \
builtins/ft_exit.c \
builtins/ft_my_unset.c \
builtins/ft_export1.c \
builtins/ft_export2.c \
builtins/ft_export3.c \
builtins/ft_export4.c \
builtins/ft_pwd.c \
env/env_expand.c \
env/env_init.c \
env/env_misc.c \
env/env_str_manip.c \
env/env_tab.c \
env/env_upd_epur.c \
free/free_cmd_struct.c \
free/free_groups.c \
free/free_loop.c \
free/ft_free_misc.c \
init/init_loop.c \
init/init_env_struct.c \
init/init_groups_fdin.c \
init/init_groups_fdout.c \
init/init_heredoc.c \
init/init_heredoc_fds.c \
init/init_heredoc_expand.c \
init/init_cmd_struct.c \
init/init_cmd_struct_utils.c \
init/init_cmd_struct_utils_2.c \
init/init_utils.c \
loop/display.c \
loop/loop_utils.c \
loop/main.c \
parsing/abs_path.c \
parsing/cond_cut.c \
parsing/epur.c \
parsing/epur_h.c \
parsing/fd.c \
parsing/groups_fill.c \
parsing/groups_malloc.c \
parsing/groups_manip_data.c \
parsing/groups_utils.c \
parsing/groups_utils_2.c \
parsing/groups.c \
parsing/parse_get.c \
parsing/parsing_processes.c \
parsing/parsing_processes_2.c \
parsing/print_error.c \
parsing/quoting.c \
parsing/rights.c \
parsing/tab_manip.c \
parsing/tab_manip_utils.c \
parsing/to_node.c \
parsing/token_parse.c \
parsing/token_parse_2.c \
signal/signal.c

CFLAGS	= -Wextra -Wall -Werror -MMD -g3 -O2 -Wunused-function

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

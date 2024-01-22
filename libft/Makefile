NAME = libft.a

CC = cc
FLAGS = -Wall -Werror -Wextra
INC = libft.h
SRCS = ft_2d_arrays.c \
ft_ai_to_ia.c \
ft_calloc.c \
ft_char_is.c \
ft_char_is_2.c \
ft_char_mod.c \
ft_lst_one.c \
ft_lst_two.c \
ft_mem.c \
ft_put_fd.c \
ft_scan_str.c \
ft_split_append.c \
ft_split.c \
ft_str_dup.c \
ft_str_is.c \
ft_str_l.c \
ft_strlen.c \
ft_str_misc.c \
ft_str_mod.c \
ft_str_n.c \
get_next_line.c \
ft_printf_fun.c \
ft_printf_hex.c \
ft_printf_nb.c \
ft_printf_ptr.c \
ft_printf_uns.c \
ft_printf_fd.c \
ft_split_base.c \
ft_split_unbase.c \
ft_split_utils.c \
ft_split_fun.c \
ft_split_fun2.c \
ft_epur.c \
ft_strlen_misc.c \
ft_str_occ.c \
ft_has_only.c \
ft_split_epured.c \
ft_free.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS} ${INC} ${SRCS}
	${CC} ${FLAGS} -c ${SRCS} -include ${INC}
	ar rc $@ ${OBJS}

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all fclean clean re
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 00:25:16 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/01 21:55:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# define SIZE_MAX (65535)

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

/*
typedef struct s_gnl
{
	char	*snake;
	char	*snake2;
	int		rendusize;
	int		memo;
	int		readsize;
}	t_gnl;

char	*get_next_line(int fd);
char	*rendu_in_preparation(char *buffer, char *rendu, t_gnl *data, int fd);
char	*makerendu(char *buffer, char *rendu, int remember, int back);
char	*ouroboros(char *buffer, t_gnl *data, int *remember, int fd);
void	feedsnake(t_gnl *data, int i);
int		ft_init(t_gnl *data);
void	ft_reinit(t_gnl *d, int remember);
char	*resnake(t_gnl *d, int i);
*/

char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(char c);
int		ft_isprint(int c);
int		ft_iswhitespace(char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t n);
int		ft_scanstr(char *str, char c);
int		ft_strbase(char *str, const char *base);
char	*ft_strdup_limiters(char *str, int from, int until);

void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_2d_lines(char **array);
int		ft_2d_has_doubles(char **arr);
int		ft_len_2d_array(char **arr);
char	**ft_copy_2d_array(char **arr, int from, int len);
void	ft_free_2d_array(char **array);
int		ft_strocc(char *str, char c);
int		ft_ustrlen(unsigned char *str);
int		ft_strindex(char *str, char c);
int		ft_strendswith(char *str, char *end);
int		ft_str_only_sep(char *str, char sep);
int		ft_isint(char *str);

char	**ft_mod_split(char const *s, char c, char append);

int		ft_printf_fd(int fd, const char *str, ...);
int		ft_printf_hex(unsigned int nb, const char type, int fd);
int		ft_printf_char(int c, int fd);
int		ft_printf_str(char *str, int fd);
int		ft_printf_uns(unsigned int nb, int fd);
int		ft_printf_ptr(unsigned long long int ptr, int fd);
int		ft_printf_nb(long int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

char	**ft_split_base(char const *s, char *base);
char	**ft_split_unbase(char const *s, char *base);
bool	ft_only_sep_unbase(char *str, char *base);
bool	ft_only_sep_base(char *str, char *base);
char	**ft_split_entry_exit(char *str);
int		ft_char_in_base(char c, const char *base);
char	*ft_str_epur(char *str, char to_remove);
void	ft_arr_epur(char **arr, char to_remove);
int		ft_strlen_from(char *str, int from);
int		ft_strlen_base(char *str, char *base, int from);
int		ft_strlen_unbase(char *str, char *base, int from);
int		ft_strocc_base(char *str, char *base);
int		ft_strocc_unbase(char *str, char *base);
char	**ft_split_fun(char *s, bool (*fun)(char*, int));
void	ft_split_do(char *s, int *i, bool (*fun)(char*, int), int which);
int		ft_strocc_from(char *str, char c, int from);
bool	ft_has_only_before(char *s, int i, int (*fun)(char));
bool	ft_has_only_after(char *s, int i, int (*fun)(char));
char	**ft_split_epured(char *s, char *m, char c);
void	ft_split_do_1(char *s, char *m, int *i, char c);
void	ft_split_do_2(char *s, char *m, int *i, char c);
bool	ft_russian_str(char *hay, char *needle);
size_t	ft_russian_index(char *hay, char *needle);
bool	ft_str_add(char **str1, char **to_add);
void	ft_set_char_to_null(char **str1, char **str2, char **str3);
void	ft_multiple_free(char **str1, char **str2, char **str3);
//void	ft_split_do_ms(char *s, char *m, int *i, int w);

#endif

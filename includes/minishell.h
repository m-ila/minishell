/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/28 15:09:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/types.h>

# define BASE_QUOTES "\'\""
# define S_QUOTE '\''
# define D_QUOTE '\"'
/* COMMENT : test with bash but not so sure about the space */
# define CHAR_END_INPUT "<>|& \t\n"
# define BASE_TOKEN "<>|"
# define BASE_WHITESP " \b\t\v\r\f"
# define SYNTAX_ERR "minishell: syntax error near unexpected token '"

# define R_EX_OK 0
# define R_ERR_GEN 1
# define R_ERR_SH_B 2

typedef struct s_env_node {
	char				*n_tag;
	char				*n_content;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env {
	char		**env;
	t_env_node	*node_;
}	t_env;

typedef struct s_data
{
	char	*input;
	char	*cwd;
	char	*prompt;
	t_env	*env_struct;
	// int	pipes;
}t_data;

/* respectivement < > << >> | $ ? */
typedef enum s_tokens
{
	redir_in = 1,
	redir_out = 2,
	redir_in_app = 3,
	redir_out_app = 4,
	pipe_ = 5,
	dollar = 6,
	question = 7
}t_tokens;

/* CMD_W_ARGS should be char** dsl */
typedef struct s_cmd {
	struct s_cmd	*previous;
	struct s_cmd	*next;
	char			*prev_token;
	char			*next_token;
	bool			b_redir;
	int				fd_in;
	int				fd_out;
	bool			b_abs_path;
	bool			b_builtin;
	char			**cmd_w_arg;
	char			*cmd;
	int				nb_s_quote;
	int				nb_d_quote;
	bool			b_has_quote;
	char			quote_used;
}	t_cmd;

typedef struct s_parse {
	int			token_nb;
	int			start_w_val_tok;
	char		**arr_token;
	t_cmd		*cmds;
	char		**arr_input;
	t_env		*env_struct;
	t_data		*data_struct;
}	t_parse;

/*======================= ENV FOLDER =======================*/
/* env_actual.c */
bool		ft_exists_in_env(t_env_node *envi, char *tag_);
char		*ft_get_tag_or_cont(char *str, char t_or_c);
void		ft_actualize_env(t_env_node *envi, char *str);
/* env_del.c */
t_env_node	*ft_find_node(t_env_node **envi, char *tag_);
t_env_node	*ft_find_prev_node(t_env_node **envi, char *tag_);
void		ft_env_del_elem(t_env_node **envi, char *tag_);
/* env_display.c */
void		ft_env_update(t_env_node *envi, char *tag_, char *cont);
void		ft_env_display(t_env_node **envi);
/* env_free.c */
void		ft_free_node(t_env_node *curr);
void		ft_env_free(t_env_node *envi);
/* env_init.c */
t_env		*ft_init_envi(char **envp);
t_env_node	*ft_create_node(char *content_, char *tag_, char *cont);
void		ft_add_envi_node(t_env_node **src, t_env_node *to_add);
t_env		*ft_init_no_envi(void);

/*======================= UTILS FOLDER =======================*/
char		**ft_split_unbase(char const *s, char *base);
char		**ft_split_base(char const *s, char *base);
char		**ft_split_entry_exit(char *str);
bool		ft_only_sep_base(char *str, char *base);
bool		ft_only_sep_unbase(char *str, char *base);
/* utils/ft_2d_array.c */
int			ft_2d_lines(char **array);
void		ft_free_2d_array(char **array);
char		**ft_copy_2d_array(char **arr, int from, int len);
int			ft_len_2d_array(char **arr);
int			ft_2d_has_doubles(char **arr);
/* utils/ft_str_utils.c */
char		*ft_strdup_limiters(char *str, int from, int until);
int			ft_strindex(char *str, char c);
int			ft_strbase(char *str, const char *base);
int			ft_char_in_base(char c, const char *base);
/* utils/ft_str_utils_2.c */
int			ft_strocc(char *str, char c);
int			ft_strocc_base(char *str, char *base);
/* utils/ft_epur.c */
char		*ft_str_epur(char *str, char to_remove);
void		ft_arr_epur(char **arr, char to_remove);
/* utils/ft_strlen_misc.c */
int			ft_strlen_from(char *str, int from);
int			ft_strlen_base(char *str, char *base, int from);

/*======================= PARSING FOLDER =======================*/
/* parsing/parse_input.c */
int			ft_parse_input(char *str, t_parse *ms);
t_cmd		*ft_go_to_last_cmd_node(t_cmd *cmd_node);
t_cmd		*ft_fill_cmd_struct(t_parse *ms);
int			ft_assign_tokens_values(t_cmd *ret, t_parse *ms, int i);
t_cmd		*ft_create_cmd_node(t_parse *ms, int i);
/* parsing/token_parse.c */
bool		ft_is_valid_token(char *str);
int			ft_get_valid_token_nb(char **token_arr, char *str);
int			ft_starts_with_valid_token(char *str);
/* parsing/print_error.c */
void		ft_msg_end(char *str, char type, bool del_struct, t_parse *ms);
void		ft_free_cmds(t_cmd **cmds);
void		ft_free_all(t_parse *ms);
/* parsing/cmd_arr_parse.c */
bool		ft_is_valid_cmd(char *str);

#endif 
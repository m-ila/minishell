/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/30 22:03:09 by mbruyant         ###   ########.fr       */
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
# include <sys/types.h>
# include "../libft/libft.h"

/* ========================== DEFINE BASE =================================== */
# define BASE_QUOTES "\'\""
# define S_QUOTE '\''
# define D_QUOTE '\"'
/* COMMENT : test with bash but not so sure about the space */
# define CHAR_END_INPUT "<>|& \t\n"
# define BASE_TOKEN "<>|"

/* ========================== DEFINE MSG ==================================== */
# define SYNTAX_ERR "syntax error near unexpected token '"
# define PRINT_SEP_T "========================= DATA ========================="
# define PRINT_SEP_C "========================= CMDS ========================="
# define PRINT_SEP "========================================================"

/* ========================== DEFINE RET VALUES ============================= */
# define R_EX_OK 0
# define R_ERR_GEN 1
# define R_ERR_SH_B 2

# ifndef SIZE_PATH_MAX
#  define SIZE_PATH_MAX 4096
# endif

# define NO_INDEX_FOUND -1

/* =========================== GLOB VARIABLE ================================ */
extern int g_return_val;

/* ============================ STRUCTURES ================================== */
typedef struct s_env_node {
	char				*n_tag;
	char				*n_content;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env {
	char		**env;
	t_env_node	*node_;
}	t_env;

/* respectivement < > << >> | $ ? */
typedef enum s_tokens
{
	redir_in,
	redir_out,
	redir_in_app,
	redir_out_app,
	pipe_,
	dollar,
	question,
	space,
	end,
	word
}t_tokens;

typedef struct s_cmd {
	struct s_cmd	*prev;	
	struct s_cmd	*next;
	char			*prev_token;
	char			*next_token;
	bool			b_redir;
	int				fd_in;
	int				fd_out;
	bool			b_abs_path;
	bool			b_builtin;
	char			*raw_str;
	char			**cmd_w_arg;
	char			*cmd;
	int				nb_s_quote;
	int				nb_d_quote;
	bool			b_has_quote;
	char			quote_used;
}	t_cmd;

typedef struct s_parse {
	int		token_nb;
	bool	start_w_val_tok;
	t_cmd	*struct_cmds;
}	t_parse;

typedef struct s_data {
	char			*user_input;
	char			*curr_work_dir;
	char			*prev_work_dir;
	char			*printed_line;
	char			**arr_token;
	char			**arr_input;
	t_env			*env_struct;
	t_parse			*parse_struct;
	bool			b_temoin;
}	t_data;

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
t_env_node	*ft_get_node(t_env_node *env_node, char *tag_);
/* env_free.c */
void		ft_free_node(t_env_node *curr);
void		ft_env_free(t_env_node *envi);
/* env_init.c */
t_env		*ft_init_envi(char **envp);
t_env_node	*ft_create_node(char *content_, char *tag_, char *cont);
void		ft_add_envi_node(t_env_node **src, t_env_node *to_add);
t_env		*ft_init_no_envi(void);

/*======================= FREE FOLDER =======================*/
/* free/free_cmd_struct.c */
void		ft_free_cmds(t_cmd *cmds);

/*======================= INIT FOLDER ========================*/
/* init/init_loop.c */
bool		ft_first_init(t_data *ms, char **envp);
bool		ft_malloc_curr_cwd(t_data *ms);
bool		ft_get_cwd(t_data *ms, unsigned int i);
bool		ft_malloc_s_parse(t_data *ms);
void		ft_update_env_cwd(t_data *ms);
/* init/init_env_struct.c */
bool		ft_env_struct_init(t_data *ms, char **envp);
void		ft_increment_shlvl(t_env_node *envi);
/* init/init_cms_struct.c */
void		ft_add_node_to_cmds(t_cmd **cmds, t_cmd *to_add);
t_cmd		*ft_create_cmd_node(char *raw_cmd);
t_cmd		*ft_go_to_last_cmd_node(t_cmd *cmd_node);
bool		ft_cmd_struct(t_data *ms, char *user_input);
void		ft_cmd_display(t_cmd *cmds);

/*======================= LOOP FOLDER ========================*/
void		ft_loop(t_data *ms);

/*======================= PARSING FOLDER =======================*/
/* parsing/parse_user_input.c */
int			ft_first_layer_parse(char *user_input, t_data *ms);
int			ft_get_next_token_index(char *user_input, int from);
/* parsing/token_parse.c */
bool		ft_is_valid_token(char *str);
int			ft_get_valid_token_nb(char **token_arr, t_data *ms);
int			ft_starts_with_valid_token(char *str);
/* parsing/print_error.c */
void		ft_msg_end(char *str, char type, bool del_struct, t_data *ms);
char		*ft_msg_ret_char(char *str);
/* parsing/cmd_arr_parse.c */
bool		ft_is_valid_cmd(char *str);
/* parsing/quoting.c */
bool		ft_str_has_quotes(char *user_input);
char		*ft_expand_quoted_substr(char **array, char quote, \
int from, int until);

#endif 
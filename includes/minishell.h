/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/10 14:47:50 by mbruyant         ###   ########.fr       */
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
# define ERR_GEN_M_CMDS "malloc error gen arr cmds"
# define ERR_GEN_M_TKS "malloc error gen arr tokens"
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
/*int	g_return_val;*/

/* ============================ STRUCTURES ================================== */

/* respectivement < > << >> | $ ? */
typedef enum s_tokens
{
	redir_in,
	redir_out,
	heredoc,
	redir_out_app,
	pipe_,
	double_quote,
	single_quote,
	dollar,
	question,
	space,
	delimiter,
	end_of_file,
	str,
	var,
	error
}t_tokens;

typedef struct s_cmd {
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			*prev_token;
	char			*next_token;
	t_tokens		tok_prev_token;
	t_tokens		tok_next_token;
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
	char			**envi;
	t_parse			*parse_struct;
	bool			b_temoin;
	char			*tmp_str;
}	t_data;

/*===================== BUILTINS FOLDER ====================*/
/* builtins/builtins.c */
int			ft_builtin(t_cmd *cmds, t_data *ms);
bool		ft_is_builtin(char *str);
/* builtins/ft_cd.c */
/* builtins/ft_echo.c */
int			ft_echo(t_cmd *cmds);
/* builtins/ft_env.c */
int			ft_env(t_data *ms);
/* builtins/ft_export.c */
/* builtins/ft_pwd.c */
int			ft_pwd(t_data *ms);
/* builtins/ft_my_unset.c */
int			ft_my_unset(t_cmd *cmds, t_data *ms);
/*======================= ENV FOLDER =======================*/
/* env/env_tab.c */
int			ft_env_init(char **envp, t_data *ms);
int			ft_init_no_env(t_data *ms);
bool		ft_tag_is_in_env(t_data *ms, char *tag);
int			ft_actualise_env(t_data *ms, char *tag, char *val);
bool		ft_increment_shlvl(t_data *ms, char **envi);
void		ft_env_display(t_data *ms);
int			ft_delete_in_env(t_data *ms, char *tag);
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
char		*ft_get_val_in_env(char **env, char *tag, t_data *ms);
/* init/init_cms_struct.c */
void		ft_add_node_to_cmds(t_cmd **cmds, t_cmd *to_add);
t_cmd		*ft_create_cmd_node(char *raw_cmd);
t_cmd		*ft_go_to_last_cmd_node(t_cmd *cmd_node);
void		ft_cmd_display(t_cmd *cmds);
bool		ft_parse_cmd(t_cmd *cmds, t_data *ms);

/*======================= LOOP FOLDER ========================*/
void		ft_loop(t_data *ms);

/*====================== PARSING FOLDER ======================*/
/* parsing/parse_user_input.c */
int			ft_first_layer_parse(t_data *ms);
int			ft_get_next_token_index(char *user_input, int from);
/* parsing/token_parse.c */
bool		ft_starts_with_token(char *user_input);
bool		ft_is_valid_token(char *str);
bool		ft_is_valid_entry_token(char *str);
int			ft_get_valid_token_nb(char **token_arr, t_data *ms);
/* parsing/print_error.c */
void		ft_msg_end(char *str, char type, bool del_struct, t_data *ms);
char		*ft_msg_ret_char(char *str);
int			ft_print_msg(char *str, char type, int return_value, t_data *ms);
char		*ft_char_print_msg(char *str, char type, char *return_value, t_data *ms);
/* parsing/cmd_arr_parse.c */
bool		ft_is_valid_cmd(char *str);
/* parsing/quoting.c */
bool		ft_str_has_quotes(char *user_input);
char		*ft_expand_quoted_substr(char **array, char quote, \
int from, int until);
/* parsing/tmp.c */
void		ft_raw_parsing_process(char *user_input, t_data *ms);
bool		ft_add_next_token_to_node(char *str, t_cmd *struct_cmd);
bool		ft_add_first_prev_token_node(char *str, t_cmd *struct_cmd);
bool		ft_add_prev_token_to_node(t_cmd *struct_cmd, t_data *ms);
bool		ft_parsing_start_token_process(char *user_input, int *from, t_data *ms);
bool		ft_parsing_token_process(char *user_input, int *from, t_data *ms);
bool		ft_parsing_cmd_process(char *user_input, int *from, t_data *ms);
int			deal_with_token(char *str, char *tok_str, int from, t_data *ms);
char		*get_token(char *str, int from);
char		*get_cmd(char *str, int from);
int			get_index_next_token(char *str, int from);
/* parsing/tmp2.c */
t_tokens    ft_which_redir_token(char *str, char which);
bool		ft_add_token_val_to_struct(t_cmd *cmds);

#endif 
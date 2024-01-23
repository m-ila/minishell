/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/23 11:33:30 by mbruyant         ###   ########.fr       */
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
# include <signal.h>
# include <sys/types.h>
# include "../libft/libft.h"
/* ========================== DEFINE BASE =================================== */
# define BASE_QUOTES "\'\""
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define BASE_TOKEN "<>|"
# define B_X "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_?"
/* ========================== DEFINE MSG ==================================== */
# define SYNTAX_ERR "syntax error near unexpected token '"
# define SYNTAX_ERR_Q "syntax error - unclosed quotes '"
# define ERR_GEN_M_CMDS "malloc error gen arr cmds"
# define ERR_GEN_M_TKS "malloc error gen arr tokens"
# define PRINT_SEP_T "========================= DATA ========================="
# define PRINT_SEP_C "========================= CMDS ========================="
# define PRINT_SEP "========================================================"
# define CD_N_F "not a file or folder\n"
# define CD_ARG "too many arguments\n"
# define M_USR "minishell_user@"
/* ========================== DEFINE RET VALUES ============================= */
# define R_EX_OK 0
# define R_ERR_GEN 1
# define R_ERR_SH_B 2
# define R_CMD_N_EX 126
# define R_CMD_N_F 127
# define R_CTRL_C 130

# ifndef SIZE_PATH_MAX
#  define SIZE_PATH_MAX 4096
# endif

# define NO_INDEX_FOUND -1
# define NOT_QUOTED 0
# define SINGLE_QUOTED 1
# define DOUBLE_QUOTED 2
/* =========================== GLOB VARIABLE =============================== */
extern int	g_return_val;
/* ============================ STRUCTURES ================================= */
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
	error,
	start
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
	char			*ep_model;
	char			*other_model;
	char			*epured_str;
	char			**cmd_w_arg;
	char			**ep_cmd_w_arg;
	char			*cmd;
}	t_cmd;

typedef struct s_parse {
	bool	start_w_val_tok;
	int		nb_reigning_quotes;
	char	l_reign_q;
	char	*tmp_tag;
	char	*tmp_val;
	char	*str1;
	char	*str2;
	char	*str3;
	char	*model1;
	char	*model2;
	char	*model3;
	char	*tmp_str;
	char	*tmp_model;
	int		heredoc_fd;
	char	*h_lim;
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
int			ft_cd(t_cmd *cmds, t_data *ms);
/* builtins/ft_echo.c */
int			ft_echo(t_cmd *cmds);
char		*ft_triple_join(char *str1, char *str2, char *str3, t_data *ms);
/* builtins/ft_env.c */
int			ft_env(t_data *ms, t_cmd *c);
/* builtins/ft_exit.c */
int			ft_exit(t_data *ms, t_cmd *cmds);
/* builtins/ft_export1.c */
bool		ft_translate_tag_to_val(t_parse *p);
/* builtins/ft_export2.c */
bool		ft_export_has_eq(char *str);
int			ft_export_first_eq(char *str);
int			ft_export(t_data *ms, t_cmd *cmds);
/* builtins/ft_export3.c */
bool		ft_translate_vars(char **str, t_data *ms);
bool		ft_local_str(char *str, t_data *ms, t_cmd *c);
bool		ft_exp_in_env(char *t, char *v, t_data *ms);
/* builtins/ft_export4.c */
bool		ft_export_bad_char(char **t, char **v);
bool		ft_export_valid_entry(char *str, char **t, char **v, int phase);
bool		ft_export_spe_cases(char **t, char **v);
/* builtins/ft_pwd.c */
int			ft_pwd(t_data *ms);
/* builtins/ft_my_unset.c */
int			ft_my_unset(t_cmd *cmds, t_data *ms);
/*======================= ENV FOLDER =======================*/
/* env/env_expand.c */
bool		ft_join_values(t_data *ms, t_cmd *cmds, int *i);
bool		ft_var_env(t_data *ms, t_cmd *cmds);
bool		ft_do_in_env(t_data *ms, t_cmd *cmds, t_parse *ps, int *i);
/* env/env_init.c */
int			ft_env_init(char **envp, t_data *ms);
int			ft_init_no_env(t_data *ms);
/* env/env_misc.c */
bool		ft_increment_shlvl(t_data *ms, char **envi);
void		ft_env_display(t_data *ms);
/* env/env_str_manip.c */
char		*ft_get_val_to_search_in_env(t_data *ms, t_cmd *cmds, int from);
char		*ft_join_tag_and_val(char *tag, char *val);
/* env/env_tab.c */
bool		ft_tag_is_in_env(t_data *ms, char *tag);
int			ft_actualise_env(t_data *ms, char *tag, char *val);
int			ft_delete_in_env(t_data *ms, char *tag);
int			ft_add_in_env(t_data *ms, char *tag_, char *cont);
/* env/env_upd_epur.c */
bool		ft_update_epur(t_data *ms, t_cmd *cmds, int *i);
/*======================= FREE FOLDER =======================*/
/* free/free_cmd_struct.c */
void		ft_free_cmds(t_cmd *cmds);
/* free/ft_free_misc.c */
int			ft_free_return(char **str1, char **str2, char **str3, int ret);
int			ft_free_ret_2(char **str1, char **str2, char ***two_dim, int ret_v);
int			ft_free_expand(t_parse **p, char **str1, char **str2, int ret);
/*======================= INIT FOLDER ========================*/
/* init/init_loop.c */
bool		ft_first_init(t_data *ms, char **envp);
bool		ft_malloc_curr_cwd(t_data *ms);
bool		ft_get_cwd(t_data *ms, unsigned int i);
bool		ft_malloc_s_parse(t_data *ms);
void		ft_update_env_cwd(t_data *ms);
/* init/init_heredoc.c */
int			ft_open_h_fd(t_data *ms, t_parse *p);
int			ft_heredoc_line(t_data *ms, t_parse *p);
int			ft_write_in_fd(t_data *ms, t_parse *p, char *cont);
int			ft_heredoc(t_data *ms, t_parse *p);
/* init/init_env_struct.c */
char		*ft_get_val_in_env(char **env, char *tag, t_data *ms);
char		*ft_quote_the_val(char *str, t_data *ms);
/* init/init_cmd_struct_utils.c */
t_cmd		*ft_create_cmd_node(char *raw_cmd);
t_cmd		*ft_go_to_last_cmd_node(t_cmd *cmd_node);
void		ft_add_node_to_cmds(t_cmd **cmds, t_cmd *to_add);
/* init/init_cmd_struct.c */
bool		ft_parse_cmd(t_cmd *cmds, t_data *ms);
bool		ft_empty_cmd(t_cmd *cmds, t_data *ms);
bool		ft_set_val_ret(t_data *ms, bool ret);
/*======================= LOOP FOLDER ========================*/
/* loop/display.c */
void		print_values(t_data *ms);
void		ft_cmd_display(t_data *ms, t_cmd *cmds);
/* loop/main.c */
void		ft_loop(t_data *ms);
void		ft_free_prompt(t_data **ms);
/*====================== PARSING FOLDER ======================*/
/* parsing/cond_cut.c */
bool		ft_cond_cut(char *str, int i);
bool		ft_export_cond_cut(char *str, int i);
bool		ft_cut_only_quotes(char *str, int i);
/* parsing/epur.c */
char		*ft_ep_model(char *s, bool (*fun)(char *, int));
char		*ft_epured_str(char *str, char *model);
/* parsing/parse_get.c */
char		*get_token(char *str, int from);
char		*get_cmd(char *str, int from);
int			get_index_next_token(char *str, int from);
/* parsing/parsing_processes.c */
void		ft_raw_parsing_process(char *user_input, t_data *ms);
bool		ft_parsing_start_token_process(char *user_input, \
int *from, t_data *ms);
bool		ft_parsing_token_process(char *user_input, int *from, t_data *ms);
bool		ft_parsing_cmd_process(char *user_input, int *from, t_data *ms);
int			deal_with_token(char *str, char *tok_str, int from, t_data *ms);
/* parsing/token_parse.c */
bool		ft_starts_with_token(char *user_input);
bool		ft_is_valid_token(char *str);
bool		ft_is_valid_entry_token(char *str);
t_tokens	ft_which_redir_token(char *str, char which);
bool		ft_add_token_val_to_struct(t_cmd *cmds);
/* parsing/print_error.c */
void		ft_msg(char *str, char type, bool del_struct, t_data *ms);
char		*ft_msg_ret_char(char *str);
int			ft_print_msg(char *str, char type, int return_value, t_data *ms);
char		*ft_char_print_msg(char *str, char type, \
char *return_value, t_data *ms);
/* parsing/quoting_rule.c */
int			ft_elem_is_in_quotes(char *str, int i);
bool		ft_count_reigning_quotes(char *str, t_parse *parse_struct);
bool		ft_char_is_a_reigning_quote(char *str, int i);
int			ft_get_index_next_reign_quo(char *str, int from);
/* parsing/to_node.c */
bool		ft_add_next_token_to_node(char *str, t_cmd *struct_cmd);
bool		ft_add_first_prev_token_node(char *str, t_cmd *struct_cmd);
/*====================== SIGNAL  FOLDER ======================*/
/* signal/signal.c */
void		ft_reset_global(t_data *ms);
void		ft_set_r_val(int val, t_data *ms);
bool		ft_comp_var_env(int val, t_data *ms);
void		ft_ctrl_c(int val);

#endif 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/28 17:33:37 by mbruyant         ###   ########.fr       */
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
# define BASE_WHITESP " \b\t\v\r\f"
# define SYNTAX_ERR " syntax error near unexpected token '"

/* ========================== DEFINE RET VALUES ============================= */
# define R_EX_OK 0
# define R_ERR_GEN 1
# define R_ERR_SH_B 2

# ifndef SIZE_PATH_MAX
#  define SIZE_PATH_MAX 4096
# endif

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
	char		**arr_input;
	t_env		*env_struct;
	struct s_data		*data_struct;
}	t_parse;

typedef struct s_data {
	char			*prompt;
	char			*curr_work_dir;
	char			*printed_line;
	t_env			*env_struct;
	t_parse			*parse_struct;
	t_cmd			*cmd_nodes;
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
/* env_free.c */
void		ft_free_node(t_env_node *curr);
void		ft_env_free(t_env_node *envi);
/* env_init.c */
t_env		*ft_init_envi(char **envp);
t_env_node	*ft_create_node(char *content_, char *tag_, char *cont);
void		ft_add_envi_node(t_env_node **src, t_env_node *to_add);
t_env		*ft_init_no_envi(void);

/*======================= INIT FOLDER ========================*/
/* init/init_loop.c */
bool		ft_first_init(t_data *ms, char **envp);
bool		ft_malloc_curr_cwd(t_data *ms);
bool		ft_get_curr_cwd(t_data *data);
/* init/init_env_struct.c */
bool		ft_env_struct_init(t_data *ms, char **envp);

/*======================= LOOP FOLDER ========================*/
void		ft_loop(t_data *ms);

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
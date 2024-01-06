/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   former_files.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:22:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/06 14:23:22 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env_node {
	char				*n_tag;
	char				*n_content;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env {
	char		**env;
	t_env_node	*node_;
}	t_env;

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
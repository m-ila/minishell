/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:41:40 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/23 21:51:10 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Need to malloc protec ft_create_node and ft_add_envi_node */
t_env	*ft_init_envi(char **envp)
{
	int			i;
	t_env		*struct_env;
	t_env_node	*ret;
	t_env_node	*buff;

	if (!envp || !*envp)
		return (ft_init_no_envi());
	struct_env = malloc(sizeof(*struct_env));
	if (!struct_env)
		return (NULL);
	struct_env->env = envp;
	ret = NULL;
	i = 0;
	while (envp[i])
	{
		buff = ft_create_node(envp[i], NULL, NULL);
		if (!ret)
			ret = buff;
		else
			ft_add_envi_node(&ret, buff);
		i++;
	}
	struct_env->node_ = ret;
	return (struct_env);
}

t_env	*ft_init_no_envi(void)
{
	t_env		*struct_env;
	t_env_node	*env_nodes;
	int			i;

	struct_env = malloc(sizeof(*struct_env));
	if (!struct_env)
		return (NULL);
	struct_env->env = NULL;
	env_nodes = NULL;
	i = 0;
	while (i < 4)
	{
		if (i == 0)
			env_nodes = ft_create_node(NULL, "PWD", "");
		if (i == 1)
			ft_add_envi_node(&env_nodes, ft_create_node(NULL, "SHLVL", "2"));
		if (i == 2)
			ft_add_envi_node(&env_nodes, ft_create_node(NULL, "OLDPWD", ""));
		if (i == 3)
			ft_add_envi_node(&env_nodes, ft_create_node(NULL, "_", ""));
		i++;
	}
	struct_env->node_ = env_nodes;
	return (struct_env);
}

/* tested : OK*/
t_env_node	*ft_go_to_last(t_env_node *env_node)
{
	while (env_node)
	{
		if (!env_node->next)
			return (env_node);
		env_node = env_node->next;
	}
	return (NULL);
}

/* adds at the end */
/* tested : OK */
void	ft_add_envi_node(t_env_node **src, t_env_node *to_add)
{
	t_env_node	*end;

	if (!to_add)
		return ;
	if (!src)
	{
		*src = to_add;
		return ;
	}
	end = ft_go_to_last(*src);
	end->next = to_add;
}

/* tested : OK */
/* si ft_get_tag_or_cont renvoie null, quel cas ? arreter ?*/
t_env_node	*ft_create_node(char *content_, char *tag_, char *cont)
{
	t_env_node	*new;

	if (!content_ && !tag_ && !cont)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	if (content_ && !tag_ && !cont)
	{
		new->n_tag = ft_get_tag_or_cont(content_, 't');
		new->n_content = ft_get_tag_or_cont(content_, 'c');
	}
	if (!content_ && tag_ && cont)
	{
		new->n_tag = ft_strdup(tag_);
		new->n_content = ft_strdup(cont);
	}
//	if (!new->n_tag || !new->n_content)
//		print error;
	new->next = NULL;
	return (new);
}

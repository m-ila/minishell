/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:12:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 20:54:58 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_free_and_ret(char **new_env)
{
	ft_free_2d_array(new_env);
	return (0);
}

int	ft_add_in_env(t_data *ms, char *tag_, char *cont)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(ft_2d_lines(ms->envi) + 2, sizeof(char *));
	if (!new_env)
		return (ft_print_msg("malloc error add in env", 'm', 0, ms));
	while (ms->envi[i])
	{
		new_env[i] = ft_strdup(ms->envi[i]);
		if (!new_env[i])
			return (ft_free_and_ret(new_env));
		i++;
	}
	new_env[i] = ft_join_tag_and_val(tag_, cont);
	if (!new_env[i])
		return (ft_free_and_ret(new_env));
	ft_free_2d_array(ms->envi);
	ms->envi = new_env;
	return (1);
}

int	ft_delete_in_env(t_data *ms, char *tag)
{
	int		i;
	char	**env_ret;

	if (!ms || !ms->envi || !tag)
		return (0);
	if (!ft_tag_is_in_env(ms, tag))
		return (0);
	env_ret = ft_calloc(ft_2d_lines(ms->envi), sizeof(char *));
	if (!env_ret)
		return (ft_print_msg("malloc error delete in env", 'm', 0, ms));
	i = 0;
	while (ft_strncmp(tag, ms->envi[i], ft_strlen_base(ms->envi[i], "=", 0)))
	{
		env_ret[i] = ft_strdup(ms->envi[i]);
		i++;
	}
	i++;
	while (ms->envi[i])
	{
		env_ret[i - 1] = ft_strdup(ms->envi[i]);
		i++;
	}
	ft_free_2d_array(ms->envi);
	ms->envi = env_ret;
	return (1);
}

static int	ft_nest_actu_env(t_data *ms, char *tag, char *val, char ***env_ret)
{
	int	i;

	i = 0;
	while (ft_strncmp(tag, ms->envi[i], ft_strlen_base(ms->envi[i], "=", 0)))
	{
		(*env_ret)[i] = ft_strdup(ms->envi[i]);
		i++;
	}
	(*env_ret)[i] = ft_join_tag_and_val(tag, val);
	if (!(*env_ret)[i])
		return (ft_print_msg("couldn't join tag and val", 'm', 0, ms));
	i++;
	while (ms->envi[i])
	{
		(*env_ret)[i] = ft_strdup(ms->envi[i]);
		i++;
	}
	return (1);
}

/*
message d'erreur si variable pas dans env ?
doit changer la variable globale ?
*/
int	ft_actualise_env(t_data *ms, char *tag, char *val)
{
	char	**env_ret;
	char	*v;

	if (!ms || !ms->envi || !tag || !val)
		return (0);
	if (!ft_tag_is_in_env(ms, tag))
		return (0);
	v = ft_get_val_in_env(ms->envi, tag, ms);
	if (!v)
		return (0);
	if (!ft_strncmp(v, val, INT_MAX))
		return (ft_free_return(&v, NULL, NULL, 1));
	free(v);
	env_ret = ft_calloc(ft_2d_lines(ms->envi) + 1, sizeof(char *));
	if (!env_ret)
		return (ft_print_msg("malloc error actualise env", 'm', 0, ms));
	if (!ft_nest_actu_env(ms, tag, val, &env_ret))
		return (0);
	ft_free_2d_array(ms->envi);
	ms->envi = env_ret;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:12:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/10 10:32:02 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env_display(t_data *ms)
{
	int	i;

	if (!ms || !ms->envi)
		return ;
	i = 0;
	while (ms->envi[i])
	{
		ft_printf_fd(1, "%s\n", ms->envi[i]);
		i++;
	}
}

bool	ft_increment_shlvl(t_data *ms, char **envi)
{
	int		value;
	char	*str;

	if (!ms || !ms->envi)
		return (false);
	str = ft_get_val_in_env(envi, "SHLVL", ms);
	if (!str)
		return (false);
	value = ft_atoi(str);
	value++;
	free(str);
	str = ft_itoa(value);
	if (!str)
		return (false);
	ft_actualise_env(ms, "SHLVL", str);
	free(str);
	return (true);
}

bool	ft_tag_is_in_env(t_data *ms, char *tag)
{
	int	i;

	if (!ms || !ms->envi || !tag || !*tag)
		return (false);
	i = 0;
	while (ms->envi[i])
	{
		if (!ft_strncmp(tag, ms->envi[i], \
		ft_strlen_base(ms->envi[i], "=", 0)))
			return (true);
		i++;
	}
	return (false);	
}

char	*ft_join_tag_and_val(char *tag, char *val)
{
	char	*str;
	int		str_len;
	int		i;
	int		j;

	if (!tag || !val)
		return (NULL);
	str_len = ft_strlen(tag) + ft_strlen(val) + 1;
	str = ft_calloc(str_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (tag[i])
	{
		str[i] = tag[i];
		i++;
	}
	str[i] = '=';
	while (val[j])
	{
		str[i + 1 + j] = val[j];
		j++;
	}
	return (str);
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
		env_ret[i] = ft_strdup(ms->envi[i]);
		i++;
	}
	ft_free_2d_array(ms->envi);
	ms->envi = env_ret;
	return (1);
}

/*
message d'erreur si variable pas dans env ?
doit changer la variable globale ?
*/
int	ft_actualise_env(t_data *ms, char *tag, char *val)
{
	int		i;
	char	**env_ret;

	if (!ms || !ms->envi || !tag || !val)
		return (0);
	if (!ft_tag_is_in_env(ms, tag))
		return (0);
	env_ret = ft_calloc(ft_2d_lines(ms->envi) + 1, sizeof(char *));
	if (!env_ret)
		return (ft_print_msg("malloc error actualise env", 'm', 0, ms));
	i = 0;
	while (ft_strncmp(tag, ms->envi[i], ft_strlen_base(ms->envi[i], "=", 0)))
	{
		env_ret[i] = ft_strdup(ms->envi[i]);
		i++;
	}
	env_ret[i] = ft_join_tag_and_val(tag, val);
	if (!env_ret[i])
		return (ft_print_msg("couldn't join tag and val", 'm', 0, ms));
	i++;
	while (ms->envi[i])
	{
		env_ret[i] = ft_strdup(ms->envi[i]);
		i++;
	}
	ft_free_2d_array(ms->envi);
	ms->envi = env_ret;
	return (1);
}

int	ft_init_no_env(t_data *ms)
{
	int		i;
	char	**env_tab;

	env_tab = ft_calloc(4, sizeof(char *));
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			env_tab[i] = ft_strdup("PWD=");
		if (i == 1)
			env_tab[i] = ft_strdup("SHLVL=1");
		if (i == 2)
			env_tab[i] = ft_strdup("_=");
		if (!env_tab[i])
		{
			ft_free_2d_array(env_tab);
			return (ft_print_msg("gen of envp arr", 'm', 0, ms));
		}
		i++;
	}
	ms->envi = env_tab;
	return (1);
}

int	ft_env_init(char **envp, t_data *ms)
{
	char	**env_cpy;

	if (!ms)
		return (0);
	if (!envp || !*envp)
		return (ft_init_no_env(ms));
	env_cpy = ft_copy_2d_array(envp, 0, ft_2d_lines(envp));
	if (!env_cpy)
		return (ft_print_msg("gen copy of envp", 'm', 0, ms));
	ms->envi = env_cpy;
	return (1);
}

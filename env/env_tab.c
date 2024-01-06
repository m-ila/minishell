/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:12:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/06 14:55:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/*
message d'erreur si variable pas dans env ?
doit changer la variable globale ?
*/
int	ft_actualise_env(t_data *ms, char *tag, char *val)
{
	int		i;
	char	*tmp;

	if (!ms || !ms->envi || !tag || !val)
		return (0);
	if (!ft_tag_is_in_env(ms, tag))
		return (0);
	i = 0;
	while (ft_strncmp(tag, ms->envi[i], ft_strlen_base(ms->envi[i], "=", 0)))
		i++;
	tmp = ft_strjoin(tag, "=");
	if (!tmp)
		return (ft_print_msg("failed to strjoin in actu env", 'm', 0, ms));
	tmp = ft_strjoin(tmp, val);
	if (!tmp)
		return (ft_print_msg("failed to strjoin in actu env", 'm', 0, ms));
	free(ms->envi[i]);
	ms->envi[i] = tmp;
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
		return ;
	if (!envp || !*envp)
		return (ft_init_no_env(ms));
	env_cpy = ft_copy_2d_array(envp, 0, ft_2d_lines(envp));
	if (!env_cpy)
		return (ft_print_msg("gen copy of envp", 'm', 0, ms));
	ms->envi = env_cpy;
	return (1);
}

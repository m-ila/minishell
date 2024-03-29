/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:00:00 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/01 14:58:13 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_init_no_env(t_data *ms)
{
	int		i;
	char	**env_tab;

	env_tab = ft_calloc(3, sizeof(char *));
	i = 0;
	while (i < 2)
	{
		if (i == 0)
			env_tab[i] = ft_strdup("PWD=");
		if (i == 1)
			env_tab[i] = ft_strdup("SHLVL=-1");
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
	envp = ms->envi;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/06 18:12:17 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
bool	ft_env_struct_init(t_data *ms, char **envp)
{
	t_env	*env_struct;

	env_struct = ft_init_envi(envp);
	if (!env_struct)
	{
		ft_printf_fd(2, "Gen of env_struct failed\n");
		return (false);
	}
	else
		ms->env_struct = env_struct;
	return (true);
}
*/
/*
doesn't check if tag is in env, but returns null if not found in env
*/
char	*ft_get_val_in_env(char **env, char *tag, t_data *ms)
{
	int	i;

	if (!env || !tag || !ms)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(tag, env[i], ft_strlen_base(env[i], "=", 0)))
			return (ft_strdup_limiters(env[i], \
			ft_strlen_base(env[i], "=", 0) + 1, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

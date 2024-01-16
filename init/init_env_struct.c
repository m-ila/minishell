/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/16 13:23:05 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_quote_the_val(char *str, t_data *ms)
{
	if (!str)
		return (NULL);
	return (ft_triple_join("\"", str, "\"", ms));
}

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

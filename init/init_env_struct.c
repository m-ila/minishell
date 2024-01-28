/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 21:22:18 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_quote_the_val(char *str, t_data *ms)
{
	if (!str)
		return (NULL);
	return (ft_triple_join("\"", str, "\"", ms));
}

static int	ft_strlen_base_p_o(char *str, char *base, int from)
{
	int	len_max;
	int	len;

	if (!str || !*str || !base || !*base)
		return (0);
	len_max = ft_strlen(str);
	if (from >= len_max)
		return (0);
	len = 0;
	while (from < len_max)
	{
		if (ft_char_in_base(str[from], base))
			return (len);
		if (!ft_char_in_base(str[from], base))
			len++;
		from++;
	}
	return (len + 1);
}

/*
doesn't check if tag is in env, but returns null if not found in env
*/
char	*ft_get_val_in_env(char **env, char *tag, t_data *ms)
{
	int		i;
	char	*tmp;

	if (!env || !tag || !ms)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp = ft_strdup_limiters(env[i], 0, ft_strlen_base_p_o(env[i], "=", 0));
		if (!ft_strncmp(tag, tmp, ft_strlen(tmp) + 1))
		{
			ft_multiple_free(&tmp, NULL, NULL);
			return (ft_strdup_limiters(env[i], \
			ft_strlen_base(env[i], "=", 0) + 1, ft_strlen(env[i])));
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

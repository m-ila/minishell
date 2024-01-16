/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:58:02 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/16 13:58:41 by mbruyant         ###   ########.fr       */
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
		if (ft_strncmp(ms->envi[i], "?=", ft_strlen("?= ")))
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
	if (!str || str[0] == '\0')
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

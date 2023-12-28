/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/28 17:31:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

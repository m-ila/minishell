/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:33:08 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/15 20:53:34 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_my_unset(t_cmd *cmds, t_data *ms)
{
	int	i;

	if (!ms || !cmds)
		return (R_ERR_GEN);
	i = 1;
	while (cmds->cmd_w_arg[i])
	{
		if (!ft_strncmp(cmds->cmd_w_arg[i], "SHLVL", ft_strlen("SHLVL ")))
			ft_actualise_env(ms, "SHLVL", "0");
		else if (!ft_strncmp(cmds->cmd_w_arg[i], "?", ft_strlen("? ")))
		{
			i++;
			continue ;
		}
		else
			ft_delete_in_env(ms, cmds->cmd_w_arg[i]);
		i++;
	}
	return (R_EX_OK);
}

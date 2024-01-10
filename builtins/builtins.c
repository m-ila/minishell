/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:10 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/10 19:36:35 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
ONLY TO BE CALLED IF ft_is_builtin IS TRUE
redirects one cmd to it's proper function
is able to change the value of the glob variable, and print err msg, so needs
t_data *ms
*/
int		ft_builtin(t_cmd *cmds, t_data *ms)
{
	if (!ft_strncmp(cmds->cmd, "cd", ft_strlen("cd")))
		return (ft_cd(cmds, ms));
	if (!ft_strncmp(cmds->cmd, "echo", ft_strlen("echo")))
		return (ft_echo(cmds));
	if (!ft_strncmp(cmds->cmd, "env", ft_strlen("env")))
		return (ft_env(ms));
	if (!ft_strncmp(cmds->cmd, "export", ft_strlen("export")))
		return (R_EX_OK);
	if (!ft_strncmp(cmds->cmd, "pwd", ft_strlen("pwd")))
		return (ft_pwd(ms));
	if (!ft_strncmp(cmds->cmd, "unset", ft_strlen("unset")))
		return (ft_my_unset(cmds, ms));
	return (R_ERR_GEN);
}

bool	ft_is_builtin(char *str)
{
	if (!ft_strncmp(str, "env", ft_strlen("env")))
		return (true);
	if (!ft_strncmp(str, "cd", ft_strlen("cd")))
		return (true);
	if (!ft_strncmp(str, "echo", ft_strlen("echo")))
		return (true);
	if (!ft_strncmp(str, "export", ft_strlen("export")))
		return (true);
	if (!ft_strncmp(str, "pwd", ft_strlen("pwd")))
		return (true);
	if (!ft_strncmp(str, "unset", ft_strlen("unset")))
		return (true);
	return (false);
}

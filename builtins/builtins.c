/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:10 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:11:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
ONLY TO BE CALLED IF ft_is_builtin IS TRUE
redirects one cmd to it's proper function
is able to change the value of the glob variable, and print err msg, so needs
t_data *ms
*/
int	ft_builtin(t_cmd *c, t_data *ms)
{
	if (!c)
		return (R_ERR_GEN);
	if (!ft_strncmp(c->cmd, "exit", ft_strlen("exit ")))
		return (ft_exit(ms, c));
	if (!ft_strncmp(c->cmd, "cd", ft_strlen("cd") + 1))
		return (ft_cd(c, ms));
	if (!ft_strncmp(c->cmd, "echo", ft_strlen("echo") + 1))
		return (ft_echo(c));
	if (!ft_strncmp(c->cmd, "env", ft_strlen("env") + 1))
		return (ft_env(ms, c));
	if (!ft_strncmp(c->cmd, "export", ft_strlen("export") + 1))
		return (ft_export(ms, c));
	if (!ft_strncmp(c->cmd, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(ms));
	if (!ft_strncmp(c->cmd, "unset", ft_strlen("unset") + 1))
		return (ft_my_unset(c, ms));
	return (R_ERR_GEN);
}

bool	ft_is_builtin(char *str)
{
	if (!str)
		return (false);
	if (!ft_strncmp(str, "exit", ft_strlen("exit ")))
		return (true);
	if (!ft_strncmp(str, "env", ft_strlen("env ")))
		return (true);
	if (!ft_strncmp(str, "cd", ft_strlen("cd ")))
		return (true);
	if (!ft_strncmp(str, "echo", ft_strlen("echo ")))
		return (true);
	if (!ft_strncmp(str, "export", ft_strlen("export ")))
		return (true);
	if (!ft_strncmp(str, "pwd", ft_strlen("pwd ")))
		return (true);
	if (!ft_strncmp(str, "unset", ft_strlen("unset ")))
		return (true);
	return (false);
}

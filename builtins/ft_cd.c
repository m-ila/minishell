/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:25:17 by chourael          #+#    #+#             */
/*   Updated: 2024/01/10 18:36:40 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
cd needs to update env (CWD and OLDPWD, knowing that OLDPWD needs to 
be created if it doesn't exist, aka cd has never been called before)
to deal with home, str[0] condition is false since it could be ~/Documents
so either expand str[0] == ~ as home then basically cd in HOME/Documents
better use the function (currently in init/init_env_struct.c)

	char	*ft_get_val_in_env(char **env, char *tag, t_data *ms);

as the **envp and our **envi are not directly linked yet (will be modified
in the future as it would cause problem once we launch minishell in
minishell)
as well as the function

	bool	ft_tag_is_in_env(t_data *ms, char *tag);

currently in env/env_tab.c
*/

char	*ft_deal_with_home(t_cmd *cmds, t_data *ms)
{
	if (!ft_tag_is_in_env(ms, "HOME"))
	{
		ft_msg("HOME is unmounted", 'm', false, ms);
		return (ft_strdup(""));
	}
	return (ft_get_val_in_env(ms->envi, "HOME", ms));
}

int	ft_cd(t_cmd *cmds, t_data *ms)
{
	char	*home_path;

	if (!ms || !cmds)
		return (R_ERR_GEN);
	if (!ms->b_temoin)
		return (R_EX_OK);
	if (ft_2d_lines(cmds->cmd_w_arg) > 2)
		return (ft_print_msg("cd : too many arguments", 'm', R_EX_OK, ms));
	if (ft_2d_lines(cmds->cmd_w_arg) == 1 || \
	!ft_strncmp(cmds->cmd_w_arg[1], "~", 2))
	{
		home_path = ft_deal_with_home(cmds, ms);
		if (chdir(getenv("HOME")) == -1)
		{
			perror("chdir 1");
			return (-1);
		}
	}
	else if (chdir(str) == -1)
	{
		perror("chdir 0");
		return (-1);
	}
	return (R_EX_OK);
}

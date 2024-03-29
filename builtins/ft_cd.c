/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:25:17 by chourael          #+#    #+#             */
/*   Updated: 2024/02/02 17:36:20 by mbruyant         ###   ########.fr       */
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
char	*ft_deal_with_home(t_data *ms)
{
	if (!ft_tag_is_in_env(ms, "HOME"))
	{
		ft_msg("cd: HOME not set", 'm', false, ms);
		return (ft_strdup(""));
	}
	return (ft_get_val_in_env(ms->envi, "HOME", ms));
}

static void	ft_cd_update_wd(t_data *ms)
{
	if (!ft_tag_is_in_env(ms, "OLDPWD"))
		ft_add_in_env(ms, "OLDPWD", ms->curr_work_dir);
	if (ft_tag_is_in_env(ms, "OLDPWD"))
		ft_actualise_env(ms, "OLDPWD", ms->curr_work_dir);
}

static int	ft_do(char *home_path, t_data *ms, int which)
{
	if (which == 1)
	{
		free(home_path);
		ms->b_temoin = false;
		return (R_ERR_GEN);
	}
	if (which == 2)
	{
		free(home_path);
		ms->b_temoin = false;
		return (ft_print_msg("cd : couldn't reach home_path", 'm', \
		R_ERR_GEN, ms));
	}
	if (which == 3)
	{
		free(home_path);
		return (R_EX_OK);
	}
	return (R_ERR_GEN);
}

int	ft_cd(t_node *c, t_data *ms)
{
	char	*home_path;

	if (!ms || !c)
		return (R_ERR_GEN);
	if (!ms->b_temoin)
		return (R_EX_OK);
	if (ft_2d_lines(c->ep_all_elem) > 2)
		return (ft_print_msg("", 'C', R_EX_OK, ms));
	ft_cd_update_wd(ms);
	if (ft_2d_lines(c->ep_all_elem) == 1 || \
	!ft_strncmp(c->ep_all_elem[1], "~", 1))
	{
		home_path = ft_deal_with_home(ms);
		if (home_path[0] == '\0')
			return (ft_do(home_path, ms, 1));
		if (chdir(home_path) == -1)
			return (ft_do(home_path, ms, 2));
		return (ft_do(home_path, ms, 3));
	}
	else if (chdir(c->ep_all_elem[1]) == -1)
	{
		ms->b_temoin = false;
		return (ft_print_msg(c->ep_all_elem[1], 'c', R_ERR_GEN, ms));
	}
	return (R_EX_OK);
}

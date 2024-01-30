/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_groups_fdin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:59:17 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/30 18:39:30 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
si plusieurs groupes, le heredoc va etre overwrite donc il faut trouver qqch de diff
*/
static bool	ft_which_is_last(t_data *ms, t_parse *p, t_group *grp)
{
	if (grp->gr_nb_infile <= 0)
		return (true);
	if (ft_get_token(grp->infile_arr[grp->gr_nb_infile - 1]) == heredoc)
	{
		if (!ft_close_fd(ms, grp->gr_fd_in))
			return (false);
		grp->gr_fd_in = p->heredoc_fd;
	}
	if (ft_get_token(grp->infile_arr[grp->gr_nb_infile - 1]) == redir_in)
		if (!ft_close_fd(ms, p->heredoc_fd))
			return (false);
	return (true);
}

bool	ft_redir_in_process(t_data *ms, t_group *grp, int i)
{
	char	*file_name;

	if (grp->gr_fd_in > -1 && !ft_close_fd(ms, grp->gr_fd_in))
		return (false);
	file_name = ft_get_file_name(grp->infile_arr[i]);
	if (access(file_name, F_OK | R_OK))
	{
		ft_c_errno_msg(file_name, errno);
		grp->gr_fd_in = -1;
		return (ft_free_return(&file_name, NULL, NULL, true));
	}
	grp->gr_fd_in = open(file_name, O_RDONLY, 0777);
	if (grp->gr_fd_in == -1)
	{
		ft_printf_fd(2, "minishell: error: failed to open fd for infile %s\n", \
		file_name);
		ft_set_r_val(R_ERR_GEN, ms);
		return (ft_free_return(&file_name, NULL, NULL, false));
	}
	return (ft_free_return(&file_name, NULL, NULL, true));
}

bool	ft_heredoc_open_process(t_data *ms, t_parse *p, t_group *grp, int i)
{
	if (p->heredoc_fd > -1 && ft_close_h_fd(ms, p) != R_EX_OK)
		return (false);
	if (ft_open_h_fd(ms, p) != R_EX_OK)
		return (false);
	ft_multiple_free(&p->h_lim, NULL, NULL);
	p->h_lim = ft_get_file_name(grp->infile_arr[i]);
	if (ft_heredoc_line(ms, p) != R_EX_OK)
		return (false);
	return (true);
}

bool    ft_process_fd_in(t_data *ms, t_parse *p, t_group *grp)
{
    int i;

    if (!grp)
        return (false);
    if (!grp->gr_nb_infile)
        return (true);
    i = 0;
	while (grp->infile_arr[i])
	{
		if (ft_get_token(grp->infile_arr[i]) == heredoc)
			if (!ft_heredoc_open_process(ms, p, grp, i))
				return (false);
		i++;
	}
	i = 0;
	while (grp->infile_arr[i])
	{
		if ((ft_get_token(grp->infile_arr[i]) == redir_in))
			if (!ft_redir_in_process(ms, grp, i))
				return (false);
		i++;
	}
	return (ft_which_is_last(ms, p, grp));
}

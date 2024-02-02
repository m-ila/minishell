/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_groups_fdout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:26:31 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/02 14:55:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_redir_out_app_open_process(t_data *ms, t_group *grp, int i)
{
	char	*file_name;

	if (grp->gr_fd_out > -1 && !ft_close_fd(ms, &grp->gr_fd_out))
		return (false);
	file_name = ft_get_file_name(grp->outfile_arr[i]);
	if (!access(file_name, F_OK) && access(file_name, W_OK))
	{
		ft_c_errno_msg(file_name, errno);
		return (ft_free_return(&file_name, NULL, NULL, false));
	}
	grp->gr_fd_out = open(file_name, O_WRONLY | O_APPEND | O_CREAT, \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (grp->gr_fd_out == -1)
	{
		ft_printf_fd(2, "minishell: error: failed to open fd for outfile %s\n", \
		file_name);
		ft_set_r_val(R_ERR_GEN, ms);
		return (ft_free_return(&file_name, NULL, NULL, false));
	}
	return (ft_free_return(&file_name, NULL, NULL, true));
}

bool	ft_redir_out_open_process(t_data *ms, t_group *grp, int i)
{
	char	*file_name;

	if (grp->gr_fd_out > -1 && !ft_close_fd(ms, &grp->gr_fd_out))
		return (false);
	file_name = ft_get_file_name(grp->outfile_arr[i]);
	if (!access(file_name, F_OK) && access(file_name, W_OK))
	{
		ft_c_errno_msg(file_name, errno);
		return (ft_free_return(&file_name, NULL, NULL, false));
	}
	grp->gr_fd_out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (grp->gr_fd_out == -1)
	{
		ft_printf_fd(2, "minishell: error: failed to open fd for outfile %s\n", \
		file_name);
		ft_set_r_val(R_ERR_GEN, ms);
		return (ft_free_return(&file_name, NULL, NULL, false));
	}
	return (ft_free_return(&file_name, NULL, NULL, true));
}

bool	ft_process_fd_out(t_data *ms, t_group *grp)
{
	int	i;

	if (!grp)
		return (false);
	if (!grp->gr_nb_outfile)
		return (true);
	i = 0;
	while (grp->outfile_arr[i])
	{
		if (ft_get_token(grp->outfile_arr[i]) == redir_out)
			if (!ft_redir_out_open_process(ms, grp, i))
				return (false);
		if (ft_get_token(grp->outfile_arr[i]) == redir_out_app)
			if (!ft_redir_out_app_open_process(ms, grp, i))
				return (false);
		i++;
	}
	return (true);
}

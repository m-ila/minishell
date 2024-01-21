/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:45:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/21 16:47:33 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_open_h_fd(t_data *ms, t_parse *p)
{
	if (!ms->b_temoin || !p)
		return (R_ERR_GEN);
	p->heredoc_fd = open("/usr/tmp/ms_hdoc.tmp", O_CREAT | O_APPEND, 0777);
	if (p->heredoc_fd == -1)
	{
		ft_msg("failed to open heredoc fd", 'e', false, ms);
		return (R_ERR_GEN);
	}
	g_return_val = -p->heredoc_fd;
	return (R_EX_OK);
}

int	ft_close_h_fd(t_data *ms, t_parse *p)
{
	if (p->heredoc_fd > -1)
	{
		if (close(p->heredoc_fd) == -1)
		{
			ft_msg("failed to close heredoc fd", 'e', false, ms);
			ft_set_r_val(R_ERR_GEN, ms);
			return (R_ERR_GEN);
		}
		else
			ft_reset_global(ms);
		p->heredoc_fd = -1;
	}
	return (R_EX_OK);
}

int	ft_heredoc(t_data *ms, t_parse *p, t_cmd *c)
{
	ft_open_h_fd(ms, p);
	ft_write_in_fd(p);
	ft_clode_h_fd(ms, p);
	return (R_EX_OK);
}

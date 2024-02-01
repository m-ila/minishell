/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:08:34 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/01 12:10:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_open_h_fd(t_data *ms, t_parse *p, t_group *grp)
{
	if (!ms->b_temoin || !p || !grp || !grp->gr_id_str)
		return (R_ERR_GEN);
	if (grp->gr_fd_heredoc > -1 && ft_close_h_fd(ms, grp) != R_EX_OK)
	{
		ft_msg("failed to close prev heredoc fd", 'm', false, ms);
		return (R_ERR_GEN);
	}
	grp->gr_fd_heredoc = open(grp->gr_id_str, \
	O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (grp->gr_fd_heredoc == -1)
	{
		ft_msg("failed to open heredoc fd", 'm', false, ms);
		return (R_ERR_GEN);
	}
	g_return_val = -1 * grp->gr_fd_heredoc;
	return (R_EX_OK);
}

/*
enlevé le unlink du fichier ici parce qu'il devra être fait dans 
les groupes (lors du free) directement puisque un par groupe
au cas de plusieurs heredoc, le open est en O_TRUNC donc va
effacer le contenu de l'ancien
*/
int	ft_close_h_fd(t_data *ms, t_group *grp)
{
	if (grp->gr_fd_heredoc > -1)
	{
		if (close(grp->gr_fd_heredoc) == -1)
		{
			ft_msg("failed to close heredoc fd", 'm', false, ms);
			ft_set_r_val(R_ERR_GEN, ms);
			return (R_ERR_GEN);
		}
		else
			ft_reset_global(ms);
		grp->gr_fd_heredoc = -1;
	}
	return (R_EX_OK);
}

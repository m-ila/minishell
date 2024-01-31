/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:45:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/31 18:25:07 by mbruyant         ###   ########.fr       */
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
	g_return_val = -p->heredoc_fd;
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

int	ft_write_in_fd(t_data *ms, t_parse *p, char *cont, t_group *grp)
{
	size_t	index_delimiter;

	if (!cont || !p->h_lim)
		return (R_ERR_GEN);
	index_delimiter = ft_russian_index(cont, p->h_lim);
	if (write(grp->gr_fd_heredoc, cont, index_delimiter) == -1)
	{
		ft_msg("failed to write in heredoc fd", 'm', false, ms);
		return (R_ERR_GEN);
	}
	return (R_EX_OK);
}

int	ft_heredoc_line(t_data *ms, t_parse *p, t_group *grp)
{
	char	*str;
	char	*buff;

	str = ft_strdup("");
	buff = NULL;
	if (!str || !ms || !p->h_lim)
		return (R_ERR_GEN);
	while (!ft_russian_str(str, p->h_lim))
	{
		ft_printf_fd(1, "> ");
		buff = get_next_line(STDIN_FILENO);
		if (!buff)
			return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
		if (!ft_str_add(&str, &buff))
			return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
	}
	if (ft_write_in_fd(ms, p, str, grp) != R_EX_OK)
		return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
	return (ft_free_return(&str, &buff, NULL, R_EX_OK));
}

int	ft_heredoc(t_data *ms, t_parse *p, t_group *grp)
{
	if (ft_open_h_fd(ms, p, grp) != R_EX_OK)
		return (R_ERR_GEN);
	if (ft_heredoc_line(ms, p, grp) != R_EX_OK)
		return (R_ERR_GEN);
//	execute
//	if (ft_close_h_fd(ms, p) != R_EX_OK)
//		return (R_ERR_GEN);
//	delete tmp file
	return (R_EX_OK);
}

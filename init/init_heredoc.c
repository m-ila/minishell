/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:45:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/31 22:49:08 by mbruyant         ###   ########.fr       */
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

int	ft_write_in_fd(t_data *ms, t_parse *p, char *cont, t_group *grp)
{
	size_t	index_delimiter;

	if (grp->gr_fd_heredoc == -1 || !cont || !p->h_lim)
		return (R_ERR_GEN);
	index_delimiter = ft_russian_index(cont, p->h_lim);
	printf("index delimiter : %ld\n", index_delimiter);
	if (write(grp->gr_fd_heredoc, cont, index_delimiter) == -1)
	{
		ft_msg("failed to write in heredoc fd", 'm', false, ms);
		return (R_ERR_GEN);
	}
	return (R_EX_OK);
}

static int	ft_heredoc_expand(t_data *ms, char **str)
{
	t_node	*tmp;

	tmp = ft_create_cmd_node(*str);
	if (!tmp)
		return (R_ERR_GEN);
	tmp->ep_model = ft_ep_model(tmp->raw_str, ft_cut_only_quotes);
	if (!tmp->ep_model)
		return (free(tmp), R_ERR_GEN);
	ft_var_env(ms, tmp);
	free(*str);
	*str = ft_strdup(tmp->raw_str);
	ft_free_cmds(tmp);
	if (!*str)
		return (R_ERR_GEN);
	return (R_EX_OK);
}

int	ft_heredoc_line(t_data *ms, t_parse *p, t_group *grp)
{
	char	*str;
	char	*buff;
	int		tmp_fd;

	str = ft_strdup("");
	buff = NULL;
	tmp_fd = dup(STDIN_FILENO);
	g_return_val = -tmp_fd;
	if (!str || !ms || !p->h_lim || !grp)
		return (R_ERR_GEN);
	while (!ft_russian_str(str, p->h_lim))
	{
		ft_printf_fd(1, "> ");
		buff = get_next_line(tmp_fd);
		if (g_return_val == -1)
			return (ft_free_return(&str, &buff, NULL, R_EX_OK));
		if (!buff)
			return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
		if (!ft_str_add(&str, &buff))
			return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
	}
	ft_close_fd(ms, &tmp_fd);
	ft_reset_global(ms);
	if (ft_heredoc_expand(ms, &str) != R_EX_OK)
		return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
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

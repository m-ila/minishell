/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:45:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/02 13:40:16 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_write_in_fd(t_data *ms, t_parse *p, char *cont, t_group *grp)
{
	size_t	index_delimiter;

	ft_open_h_fd(ms, p, grp);
	if (grp->gr_fd_heredoc == -1 || !cont)
		return (R_ERR_GEN);
	index_delimiter = ft_strlen(cont);
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
	tmp->ep_model = ft_ep_model(tmp->raw_str, ft_leave_everything);
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

static int	ft_heredoc_do(t_data *ms, t_parse *p, char **str, \
char **buff)
{
	if (!*buff)
	{
		ft_heredoc_sig_ms(p);
		ft_close_fd(ms, &p->tmp_fd);
		return (ft_free_return(NULL, NULL, NULL, true));
	}
	if (!ft_str_add(str, buff))
	{
		return (ft_free_return(str, buff, NULL, false));
	}
	return (true);
}

static bool	ft_heredoc_miniloop(t_data *ms, t_group *grp, \
char **str, char **buff)
{
	t_parse	*p;

	p = ms->parse_s;
	p->tmp_fd = dup(STDIN_FILENO);
	g_return_val = -p->tmp_fd;
	while (1)
	{
		ft_printf_fd(1, "> ");
		*buff = get_next_line(p->tmp_fd);
		if (g_return_val == -1)
		{
			ft_close_fd(ms, &grp->gr_fd_heredoc);
			g_return_val = R_CTRL_C;
			ft_comp_var_env(ms);
			ms->b_temoin = false;
			return (ft_free_return(str, buff, NULL, true));
		}
		if (*buff && !ft_strncmp(*buff, p->h_lim, ft_strlen(*buff) - 1) \
		&& ft_strlen(*buff) - 1 > 0)
			break ;
		if (!ft_heredoc_do(ms, p, str, buff))
			return (false);
		if (p->tmp_fd == -1)
		{
			ft_close_fd(ms, &grp->gr_fd_heredoc);
			break ;
		}
	}
	ft_close_fd(ms, &p->tmp_fd);
	ft_multiple_free(buff, NULL, NULL);
	return (true);
}

int	ft_heredoc_line(t_data *ms, t_parse *p, t_group *grp)
{
	char	*str;
	char	*buff;

	str = ft_strdup("");
	buff = NULL;
	if (!str || !ms || !p->h_lim || !grp)
		return (R_ERR_GEN);
	if (!ft_heredoc_miniloop(ms, grp, &str, &buff))
		return (false);
	ft_reset_global(ms);
	if (ft_heredoc_expand(ms, &str) != R_EX_OK)
		return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
	if (ft_write_in_fd(ms, p, str, grp) != R_EX_OK)
		return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
	return (ft_free_return(&str, &buff, NULL, R_EX_OK));
}

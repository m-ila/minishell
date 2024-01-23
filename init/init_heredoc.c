/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:45:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/23 13:25:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_open_h_fd(t_data *ms, t_parse *p)
{
	if (!ms->b_temoin || !p)
		return (R_ERR_GEN);
	p->heredoc_fd = open("/tmp/heredoc.tmp", \
	O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (p->heredoc_fd == -1)
	{
		ft_msg("failed to open heredoc fd", 'm', false, ms);
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

int	ft_write_in_fd(t_data *ms, t_parse *p, char *cont)
{
	size_t	index_delimiter;

	if (!cont || !p->h_lim)
		return (R_ERR_GEN);
	index_delimiter = ft_russian_index(cont, p->h_lim);
	if (write(p->heredoc_fd, cont, index_delimiter) == -1)
	{
		ft_msg("failed to write in heredoc fd", 'e', false, ms);
		return (R_ERR_GEN);
	}
	return (R_EX_OK);
}

int	ft_heredoc_line(t_data *ms, t_parse *p)
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
	if (ft_write_in_fd(ms, p, str) != R_EX_OK)
		return (ft_free_return(&str, &buff, NULL, R_ERR_GEN));
	return (ft_free_return(&str, &buff, NULL, R_EX_OK));
}

int	ft_heredoc(t_data *ms, t_parse *p)
{
	if (ft_open_h_fd(ms, p) != R_EX_OK)
		return (R_ERR_GEN);
	if (ft_heredoc_line(ms, p) != R_EX_OK)
		return (R_ERR_GEN);
//	execute
	if (ft_close_h_fd(ms, p) != R_EX_OK)
		return (R_ERR_GEN);
//	delete tmp file
	return (R_EX_OK);
}

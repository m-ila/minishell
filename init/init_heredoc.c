/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:45:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/21 18:41:17 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_open_h_fd(t_data *ms, t_parse *p)
{
	if (!ms->b_temoin || !p)
		return (R_ERR_GEN);
	if (p->heredoc_fd == -1)
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

bool	ft_str_add(char **str1, char **to_add)
{
	char	*tmp;

	if (!str1 || !to_add)
		return (false);
	tmp = NULL;
	tmp = ft_strjoin(*str1, *to_add);
	if (!tmp)
		return (false);
	free(*str1);
	*str1 = tmp;
	ft_multiple_free(to_add, NULL, NULL);
	return (true);
}

int	ft_write_in_fd(t_data *ms, t_parse *p)
{
	char	*str;
	char	*buff;

	str = ft_strdup("");
	buff = NULL;
	if (!str || !buff || !ms)
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
	return (ft_free_return(&str, &buff, NULL, R_EX_OK));
}

int	ft_heredoc(t_data *ms, t_parse *p)
{
	if (ft_open_h_fd(ms, p) != R_EX_OK)
		return (R_ERR_GEN);
	if (ft_write_in_fd(ms, p)!= R_EX_OK)
		return (R_ERR_GEN);
//	execute
	ft_close_h_fd(ms, p);
//	delete tmp file
	return (R_EX_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:51:00 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/19 18:42:13 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_r_val(int val, t_data *ms)
{
	char	*str_val;

	g_return_val = val;
	str_val = ft_itoa(g_return_val);
	if (!val)
		ft_msg("failed to change return val", 'm', false, NULL);
	ft_actualise_env(ms, "$", str_val);
	free(str_val);
	return ;
}

void	ft_ctrl_c(int val, t_data *ms)
{
	t_parse	*p;

	p = ms->parse_struct;
	if (p->heredoc_fd > -1)
	{
		ft_printf_fd(2, "^C\n");
		close(p->heredoc_fd);
		p->heredoc_fd = -1;
		ms->b_temoin = 0;
	}
	else
	{
		ms->b_temoin = 0;
	}
	ft_set_r_val(R_CTRL_C, ms);
}
/*
void	ft_ctrl_c(int val)
{
	g_return_val = val;
}
*/

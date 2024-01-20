/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:05:26 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/20 13:19:38 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_data *ms, t_cmd *cmds)
{
	if (!cmds)
		return (R_EX_OK);
	if (ft_2d_lines(cmds->cmd_w_arg) > 1)
		return (R_EX_OK);
	ft_free_cmds(cmds);
	ft_free_prompt(&ms);
	ft_free_2d_array(ms->envi);
	free(ms->tmp_str);
	free(ms->prev_work_dir);
	free(ms->curr_work_dir);
	free(ms->parse_struct);
	free(ms);
	exit(g_return_val);
	return (R_EX_OK);
}

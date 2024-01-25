/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:05:26 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:52:39 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_data *ms, t_cmd *c)
{
	if (!c)
		return (R_EX_OK);
	ft_free_cmds(c);
	ft_free_prompt(&ms);
	ft_free_2d_array(ms->envi);
	free(ms->tmp_str);
	free(ms->prev_work_dir);
	free(ms->curr_work_dir);
	free(ms->parse_s);
	free(ms);
	exit(g_return_val);
	return (R_EX_OK);
}

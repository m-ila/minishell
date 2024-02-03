/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:49:38 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 16:51:13 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc_expand(t_data *ms, char **str)
{
	t_node	*tmp;

	tmp = ft_create_cmd_node(*str);
	if (!tmp)
		return (R_ERR_GEN);
	tmp->ep_model = ft_ep_h_model(tmp->raw_str, ft_leave_everything);
	if (!tmp->ep_model)
		return (free(tmp), R_ERR_GEN);
	ft_expand(ms, tmp);
	free(*str);
	*str = ft_strdup(tmp->raw_str);
	ft_free_cmds(tmp);
	if (!*str)
		return (R_ERR_GEN);
	return (R_EX_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:21:47 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 16:02:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_cmd_node(t_cmd *curr)
{
	if (!curr)
		return ;
	if (curr->cmd)
		free(curr->cmd);
	if (curr->cmd_w_arg)
		ft_free_2d_array(curr->cmd_w_arg);
	if (curr->ep_cmd_w_arg)
		ft_free_2d_array(curr->ep_cmd_w_arg);
	if (curr->raw_str)
		free(curr->raw_str);
	if (curr->ep_model)
		free(curr->ep_model);
	if (curr->epured_str)
		free(curr->epured_str);
	if (curr->prev_token)
		free(curr->prev_token);
	if (curr->next_token)
		free(curr->next_token);
	if (curr)
		free(curr);
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*curr;

	if (!cmds)
		return ;
	while (cmds)
	{
		curr = cmds;
		cmds = cmds->next;
		ft_free_cmd_node(curr);
	}
}

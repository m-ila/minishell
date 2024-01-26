/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:21:47 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 17:12:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_cmd_node(t_node *curr)
{
	if (!curr)
		return ;
	if (curr->cmd)
		free(curr->cmd);
	if (curr->all_elem)
		ft_free_2d_array(curr->all_elem);
	if (curr->ep_all_elem)
		ft_free_2d_array(curr->ep_all_elem);
	if (curr->cmd_w_args)
		ft_free_2d_array(curr->cmd_w_args);
	if (curr->raw_str)
		free(curr->raw_str);
	if (curr->ep_model)
		free(curr->ep_model);
	if (curr->ep_str)
		free(curr->ep_str);
	if (curr->prev_token)
		free(curr->prev_token);
	if (curr->next_token)
		free(curr->next_token);
	if (curr)
		free(curr);
}

void	ft_free_cmds(t_node *c)
{
	t_node	*curr;

	if (!c)
		return ;
	while (c)
	{
		curr = c;
		c = c->next;
		ft_free_cmd_node(curr);
	}
}

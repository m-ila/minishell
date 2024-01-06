/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 21:49:09 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/23 21:50:42 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_node(t_env_node *curr)
{
	if (!curr)
		return ;
	if (curr->n_tag)
		free(curr->n_tag);
	if (curr->n_content)
		free(curr->n_content);
	if (curr)
		free(curr);
}

void	ft_env_free(t_env_node *envi)
{
	t_env_node	*curr;

	while (envi)
	{
		curr = envi;
		envi = envi->next;
		ft_free_node(curr);
	}
}

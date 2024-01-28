/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_groups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:57:11 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 13:58:20 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_groups(t_group **gr)
{
	t_group	*index;

	if (*gr == NULL)
		return ;
	while (*gr)
	{
		index = *gr;
		(*gr) = (*gr)->next;
		if (index->infile_arr)
			ft_free_2d_array(index->infile_arr);
		if (index->outfile_arr)
			ft_free_2d_array(index->outfile_arr);
		if (index->cmd_and_args)
			ft_free_2d_array(index->cmd_and_args);
		free(index);
		index = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_groups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:57:11 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/01 13:06:07 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_groups(t_data *ms, t_group **gr)
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
		if (index->gr_id_str)
		{
			if (!access(index->gr_id_str, F_OK))
				unlink(index->gr_id_str);
			ft_multiple_free(&index->gr_id_str, NULL, NULL);
		}
		if (index->gr_fd_in > 2 && g_return_val != -1)
			ft_close_fd(ms, &index->gr_fd_in);
		if (index->gr_fd_out > 2)
			ft_close_fd(ms, &index->gr_fd_out);
		free(index);
		index = NULL;
	}
}

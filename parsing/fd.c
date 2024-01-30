/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:24:20 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/30 17:45:52 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_close_fd(t_data *ms, int fd)
{
	if (fd == -1)
		return (true);
	if (close(fd) == -1)
	{
		ft_printf_fd(2, "minishell: error: failed to close fd %d\n", fd);
		ft_set_r_val(R_ERR_GEN, ms);
		return (false);
	}
	fd = -1;
	return (true);
}

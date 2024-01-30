/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:51:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/30 17:51:51 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_errno_msg(t_node *c, int erno)
{
	if (c)
		ft_printf_fd(2, "minishell : %s : error %s\n", c->cmd, strerror(erno));
}

void	ft_c_errno_msg(char *str, int erno)
{
	if (str)
		ft_printf_fd(2, "minishell : %s : %s\n", str, strerror(erno));
}

/*
attention, si necessaire pour executer, alors il faut aussi check si existe
aussi (parsing/rights.c) !
*/
bool	ft_absolute_path(t_node *c)
{
	if ((ft_strncmp(c->cmd, "/", 1) == 0) || \
	(ft_strncmp(c->cmd, "./", 2) == 0) || (ft_strncmp(c->cmd, "../", 3) == 0))
	{
		return (true);
	}
	return (false);
}

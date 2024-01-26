/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:51:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 17:12:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_errno_msg(t_node *c, int errno)
{
    ft_printf_fd(2, "minishell : %s : error %s\n", c->cmd, strerror(errno));
}

/*
attention, si necessaire pour executer, alors il faut aussi check si existe
aussi (parsing/rights.c) !
*/
bool	ft_absolute_path(t_node *c)
{
	if ((ft_strncmp(c->cmd, "/", 1) == 0) || \
	(ft_strncmp(c->cmd, "./", 2) == 0) || \
	(ft_strncmp(c->cmd, "../", 3) == 0))
        return (true);
    return (false);
}

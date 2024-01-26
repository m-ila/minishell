/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:03:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 17:12:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* not only for docs, right ? */
bool    ft_has_exec_rights(t_node *c)
{
    if (!c || !c->b_is_file)
        return (false);
    if ((access(c->cmd, X_OK) == 0))
        return (true);
    return (false);
}

bool    ft_doc_has_write_rights(t_node *c)
{
    if (!c || !c->b_is_file)
        return (false);
    if ((access(c->cmd, W_OK) == 0))
        return (true);
    return (false);
}

bool    ft_doc_has_read_rights(t_node *c)
{
    if (!c || !c->b_is_file)
        return (false);
    if ((access(c->cmd, R_OK) == 0))
        return (true);
    return (false);
}

bool    ft_exists(t_node *c)
{
    if (!c || !c->b_is_file)
        return (false);
    if ((access(c->cmd, F_OK) == 0))
        return (true);
    return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:03:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/30 15:06:34 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* not only for docs, right ? */
bool	ft_has_exec_rights(t_node *c)
{
	if (!c || !c->b_is_file)
		return (false);
	if ((access(c->ep_all_elem[0], X_OK) == 0))
		return (true);
	return (false);
}

bool	ft_doc_has_write_rights(t_node *c)
{
	if (!c || !c->b_is_file)
		return (false);
	if ((access(c->ep_all_elem[0], W_OK) == 0))
		return (true);
	return (false);
}

bool	ft_doc_has_read_rights(t_node *c)
{
	if (!c || !c->b_is_file)
		return (false);
	if ((access(c->ep_all_elem[0], R_OK) == 0))
		return (true);
	return (false);
}

bool	ft_exists(t_node *c)
{
	if (!c || !c->b_is_file)
		return (false);
	if ((access(c->ep_all_elem[0], F_OK) == 0))
		return (true);
	return (false);
}

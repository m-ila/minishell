/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:33:08 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 08:21:53 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_my_unset(t_node *c, t_data *ms)
{
	int	i;

	if (!ms || !c)
		return (R_ERR_GEN);
	i = 1;
	while (c->ep_all_elem[i])
	{
		if (!ft_strncmp(c->ep_all_elem[i], "SHLVL", ft_strlen("SHLVL ")))
			ft_actualise_env(ms, "SHLVL", "0");
		else if (!ft_strncmp(c->ep_all_elem[i], "?", ft_strlen("? ")))
		{
			i++;
			continue ;
		}
		else
			ft_delete_in_env(ms, c->ep_all_elem[i]);
		i++;
	}
	return (R_EX_OK);
}

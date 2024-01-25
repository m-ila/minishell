/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:33:08 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:11:29 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_my_unset(t_cmd *c, t_data *ms)
{
	int	i;

	if (!ms || !c)
		return (R_ERR_GEN);
	i = 1;
	while (c->all_elem[i])
	{
		if (!ft_strncmp(c->all_elem[i], "SHLVL", ft_strlen("SHLVL ")))
			ft_actualise_env(ms, "SHLVL", "0");
		else if (!ft_strncmp(c->all_elem[i], "?", ft_strlen("? ")))
		{
			i++;
			continue ;
		}
		else
			ft_delete_in_env(ms, c->all_elem[i]);
		i++;
	}
	return (R_EX_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:33:08 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 09:59:29 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_unset_invalid_entry(char *t)
{
	bool	ret;

	ret = true;
	if (ft_strocc_unbase(t, B_X) || !ft_strlen(t) || ft_isdigit(t[0]) || \
		ft_strocc(t, '?'))
		ret = false;
	if (!ret)
	{
		ft_printf_fd(2, \
		"minishell: unset: \"%s\" : not a valid identifier\n", t);
		g_return_val = R_ERR_GEN;
	}
	return (ret);
}

int	ft_my_unset(t_node *c, t_data *ms)
{
	int	i;

	if (!ms || !c)
		return (R_ERR_GEN);
	i = 1;
	while (c->ep_all_elem[i])
	{
		g_return_val = R_EX_OK;
		if (!ft_strncmp(c->ep_all_elem[i], "SHLVL", ft_strlen("SHLVL ")))
			ft_actualise_env(ms, "SHLVL", "0");
		else if (!ft_strncmp(c->ep_all_elem[i], "?", ft_strlen("? ")))
		{
			i++;
			continue ;
		}
		else if (!ft_unset_invalid_entry(c->ep_all_elem[i]))
			ft_delete_in_env(ms, c->ep_all_elem[i]);
		i++;
	}
	return (R_EX_OK);
}

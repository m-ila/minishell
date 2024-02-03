/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manip_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:00:20 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 17:07:50 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_cpy_second_tab(char ***tab2, char ***tab_to, \
size_t *i, size_t *j)
{
	*j = -1;
	while ((*tab2)[++(*j)])
	{
		(*tab_to)[(*i) + (*j)] = ft_strdup((*tab2)[*j]);
		if (!(*tab_to)[(*i) + (*j)])
		{
			ft_free_2d_array(*tab_to);
			return (false);
		}
	}
	return (true);
}

bool	ft_add_tabs(char ***tab1, char **tab2)
{
	size_t	len_max;
	size_t	i;
	size_t	j;
	char	**tab_ret;

	if (!tab2 || \
	((!tab1 || !(*tab1)) && !ft_deal_w_empty_tab(tab1, NULL, 2)))
		return (false);
	len_max = ft_2d_lines(*tab1) + ft_2d_lines(tab2);
	tab_ret = ft_calloc(len_max + 1, sizeof(char *));
	if (!tab_ret)
		return (false);
	if (!ft_cpy_first_tab(tab1, &tab_ret, &i))
		return (ft_tab_manip_ret(tab_ret));
	if (!ft_cpy_second_tab(&tab2, &tab_ret, &i, &j))
		return (ft_tab_manip_ret(tab_ret));
	ft_free_2d_array(*tab1);
	*tab1 = tab_ret;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:35:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:12:33 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_export_has_eq(char *str)
{
	size_t	i;
	size_t	occ;

	if (!str)
		return (false);
	i = 0;
	occ = 0;
	while (str[i])
	{
		if (str[i] == '=' && !ft_elem_is_in_quotes(str, i))
			occ++;
		i++;
	}
	if (!occ)
		return (false);
	return (true);
}

int	ft_export_first_eq(char *str)
{
	size_t	i;

	if (!str)
		return (NO_INDEX_FOUND);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && !ft_elem_is_in_quotes(str, i))
			return (i);
		i++;
	}
	return (NO_INDEX_FOUND);
}

int	ft_export(t_data *ms, t_cmd *c)
{
	char	*exp_mod;
	char	*cleaned_str;
	char	**exp_split;
	int		i;

	if (!c)
		return (R_ERR_GEN);
	exp_mod = ft_ep_model(ms->user_input, ft_export_cond_cut);
	cleaned_str = ft_ep_str(ms->user_input, exp_mod);
	exp_split = ft_split_epured(ms->user_input, exp_mod, '0');
	if (!exp_mod || !cleaned_str || !exp_split)
		return (ft_free_ret_2(&exp_mod, &cleaned_str, &exp_split, R_ERR_GEN));
	i = 1;
	while (exp_split[i])
	{
		if (ft_export_valid_entry(exp_split[i], NULL, NULL, 1))
			if (!ft_local_str(exp_split[i], ms, c))
				break ;
		i++;
	}
	ft_multiple_free(&exp_mod, &cleaned_str, NULL);
	ft_free_2d_array(exp_split);
	return (R_EX_OK);
}

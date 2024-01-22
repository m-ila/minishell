/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:35:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 16:02:46 by mbruyant         ###   ########.fr       */
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

int	ft_export(t_data *ms, t_cmd *cmds)
{
	char	*export_model;
	char	*cleaned_str;
	char	**export_split;
	int		i;

	if (!cmds)
		return (R_ERR_GEN);
	export_model = ft_ep_model(ms->user_input, ft_export_cond_cut);
	cleaned_str = ft_epured_str(ms->user_input, export_model);
	export_split = ft_split_epured(ms->user_input, export_model, '0');
	if (!export_model || !cleaned_str || !export_split)
		return (ft_free_ret_2(&export_model, &cleaned_str, &export_split, R_ERR_GEN));
	i = 1;
	ft_printf_fd(1, "export model : (d)%s(f)\ncleaned str : (d)%s(f)\n", \
	export_model, cleaned_str);
	while (export_split[i])
	{
		ft_printf_fd(1, "split[%d] : (d)%s(f)\n", i, export_split[i]);
		if (ft_export_valid_entry(export_split[i], NULL, NULL, 1))
			if (!ft_local_str(export_split[i], ms, cmds))
				break ;
		i++;
	}
	ft_multiple_free(&export_model, &cleaned_str, NULL);
	ft_free_2d_array(export_split);
	return (R_EX_OK);
}

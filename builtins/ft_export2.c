/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:35:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/19 13:53:29 by mbruyant         ###   ########.fr       */
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

bool	ft_export_bad_char(char **t, char **v)
{
	char	*msg;

	msg = ft_join_tag_and_val(*t, *v);
	if (!msg)
		return (false);
	ft_msg(msg, 'e', false, NULL);
	free(msg);
	return (false);
}

bool	ft_export_spe_cases(char **t, char **v)
{
	int	value;

	if (!ft_strncmp(*t, "SHLVL", ft_strlen("SHLVL") + 1))
	{
		if (ft_has_only_after(*v, 0, ft_isdigit) && ft_isint(*v))
		{
			value = ft_atoi(*v);
			if (value > 1)
				value--;
			else
				value = 0;
			free(*v);
			*v = ft_itoa(value);
			if (!*v)
				return (false);
			return (true);
		}
		else
		{
			free(*v);
			*v = ft_strdup("0");
			if (!*v)
				return (ft_print_msg("exp spe cases", 'm', false, NULL));
			return (true);
		}
	}
	return (true);
}

bool	ft_export_valid_entry(char *str, char **t, char **v, int phase)
{
	if (!str && phase == 1)
		return (false);
	if (phase == 1)
		if (!ft_export_has_eq(str) || ft_export_first_eq(str) == -1)
			return (false);
	if (phase == 2)
	{
		if (ft_strocc_base(*t, "/\\") || !ft_strlen(*t))
			return (ft_export_bad_char(t, v));
		if ((*t[0] == '$') && ft_strlen(*t) == 1)
			return (false);
		return (ft_export_spe_cases(t, v));
	}
	return (true);
}

int	ft_export(t_data *ms, t_cmd *cmds)
{
	char	*export_model;
	char	*cleaned_str;
	char	**export_split;
	int		i;

	if (!cmds)
		return (R_ERR_GEN);
	export_model = ft_epured_model(ms->user_input, ft_export_cond_cut);
	cleaned_str = ft_epured_str(ms->user_input, export_model);
	export_split = ft_split_epured(ms->user_input, export_model, '0');
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

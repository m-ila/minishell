/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:26:23 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/02 15:13:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	ft_deal_w_val(int *v)
{
	if (*v > 1)
		(*v)--;
	else
		(*v) = 0;
}

bool	ft_export_spe_cases(char **t, char **v)
{
	int	value;

	if (!ft_strncmp(*t, "SHLVL", ft_strlen("SHLVL") + 1))
	{
		if (ft_has_only_after(*v, 0, ft_isdigit) && ft_isint(*v))
		{
			value = ft_atoi(*v);
			ft_deal_w_val(&value);
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
		if (ft_strocc_unbase(*t, B_X) || !ft_strlen(*t) || ft_isdigit(*t[0]) || \
		ft_strocc(*t, '?'))
			return (ft_export_bad_char(t, v));
		if ((*t[0] == '$') && ft_strlen(*t) == 1)
			return (false);
		return (ft_export_spe_cases(t, v));
	}
	return (true);
}

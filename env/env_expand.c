/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:31:38 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/15 11:51:36 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_val_to_search_in_env(t_data *ms, t_cmd *cmds, int from)
{
	int	until;

	if (!ms->b_temoin || !cmds->epured_model || \
	from >= (int) ft_strlen(cmds->epured_model))
		return (ft_strdup(""));
	until = ft_strlen_unbase(cmds->epured_model, "1", from);
	return (ft_strdup_limiters(cmds->raw_str, from, until));
}

bool	ft_check_valid_env_var(t_data *ms, t_cmd *cmds, char *str)
{
	if (!ms->envi || !ms->b_temoin || !cmds->epured_model || \
	!str || str[0] == '\0')
		return (false);
	if (ft_tag_is_in_env(ms, str))
		return (true);
	return (false);
}

bool	ft_var_env(t_data *ms, t_cmd *cmds)
{
	int		i;
	char	*val;

	if (!ms->b_temoin || !cmds->epured_model)
		return (false);
	i = 0;
	while (i < ft_strlen(ms->user_input))
	{
		val = NULL;
		if (cmds->epured_model[i] == '$')
		{
			val = ft_get_val_to_search_in_env(ms, cmds, i + 1);
			if (!val)
				return (ft_print_msg("env var", 'm', false, ms));
			if (ft_check_valid_env_var(ms, cmds, val))
			{
				//join
				// i += ft_strlen(val); pas +1 car i++ à la sortie
				//free val
				//update epured_model
			}
		}
		i++;
	}
}

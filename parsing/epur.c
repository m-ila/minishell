/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:33:21 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 11:39:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_assign_char(char *s, int i, char *model)
{
	if (s[i] == '$' && ft_elem_is_in_quotes(s, i) == SINGLE_QUOTED)
		model[i] = 'e';
	else if (ft_iswhitespace(s[i]))
		model[i] = 's';
	else if (ft_char_in_base(s[i], BASE_QUOTES))
		model[i] = 'q';
	else
		model[i] = '1';
}

char	*ft_epured_model(char *s)
{
	char	*model;
	int		i;

	if (!s)
		return (ft_strdup(""));
	model = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!model)
		return (ft_strdup(""));
	i = 0;
	while (s[i])
	{
		if (!ft_cond_cut(s, i))
			ft_assign_char(s, i, model);
		if (ft_cond_cut(s, i))
			model[i] = '0';
		i++;
	}
	return (model);
}

bool	ft_cond_cut(char *str, int i)
{
	if (ft_char_is_a_reigning_quote(str, i))
		return (true);
	if (ft_char_in_base(str[i], BASE_QUOTES) && \
	!ft_elem_is_in_quotes(str, i))
		return (true);
	return (false);
}

/*
void    ft_add_epured_to_cmd(t_cmd *cmds)
{
    while (cmds)
    {
        cmds->epured_model = ft_epured_model(cmds->raw_str);
        cmds = cmds->next;
    }
}
*/

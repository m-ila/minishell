/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:38:32 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/02 17:20:26 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_assign_char(char *s, int i, char *model)
{
	if (s[i] == '$' && ft_char_in_base(s[i + 1], B_X))
	{
		model[i] = '$';
		return ;
	}
	else if (!ft_char_in_base(s[i], B_X))
		model[i] = 'X';
	else
		model[i] = '1';
}

char	*ft_ep_h_model(char *s, bool (*fun)(char*, int))
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
		if (!fun(s, i))
			ft_assign_char(s, i, model);
		if (fun(s, i))
			model[i] = '0';
		i++;
	}
	return (model);
}

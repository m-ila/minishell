/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:33:21 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 16:17:12 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_assign_char(char *s, int i, char *model)
{
	if (s[i] == '$' && ((ft_elem_is_in_quotes(s, i) == DOUBLE_QUOTED || \
		ft_elem_is_in_quotes(s, i) == NOT_QUOTED) && \
		(ft_isalnum(s[i + 1]) || ft_char_in_base(s[i + 1], "?_"))))
	{
			model[i] = '$';
			return ;
	}
	if (ft_iswhitespace(s[i]))
	{
		if (((ft_has_only_before(s, i, ft_iswhitespace) || \
		ft_has_only_after(s, i, ft_iswhitespace)) && \
		ft_elem_is_in_quotes(s, i) == NOT_QUOTED) || \
		ft_elem_is_in_quotes(s, i) == NOT_QUOTED)
			model[i] = '0';
		if (ft_elem_is_in_quotes(s, i) == SINGLE_QUOTED)
			model[i] = 's';
		if (ft_elem_is_in_quotes(s, i) == DOUBLE_QUOTED)
			model[i] = 'S';
		return ;
	}
	else if (!ft_char_in_base(s[i], B_X))
		model[i] = 'X';
	else if (ft_char_in_base(s[i], BASE_QUOTES))
		model[i] = 'q';
	else
		model[i] = '1';
}

char	*ft_ep_str(char *str, char *model)
{
	char	*epured;
	int		len;
	int		i;
	int		j;

	if (!str || !model)
		return (ft_strdup(""));
	len = (int) ft_strlen(str) - ft_strocc(model, '0');
	if (len <= 0)
		return (ft_strdup(""));
	epured = ft_calloc((size_t) len + 1, sizeof(char));
	if (!epured)
		return (ft_strdup(""));
	i = 0;
	j = 0;
	while (str[i] && model[i])
	{
		if (model[i] != '0')
		{
			epured[j] = str[i];
			j++;
		}
		i++;
	}
	return (epured);
}

char	*ft_ep_model(char *s, bool (*fun)(char*, int))
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

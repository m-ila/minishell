/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_manip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:47:17 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:11:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_val_to_search_in_env(t_data *ms, t_cmd *c, int from)
{
	int	until;

	if (!ms->b_temoin || !c->ep_model || \
	from >= (int) ft_strlen(c->ep_model))
		return (ft_strdup(""));
	until = ft_strlen_unbase(c->ep_model, "1", from);
	return (ft_strdup_limiters(c->raw_str, from, from + until));
}

char	*ft_join_tag_and_val(char *tag, char *val)
{
	char	*str;
	int		str_len;
	int		i;
	int		j;

	if (!tag || !val)
		return (NULL);
	str_len = ft_strlen(tag) + ft_strlen(val) + 1;
	str = ft_calloc(str_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (tag[i])
	{
		str[i] = tag[i];
		i++;
	}
	str[i] = '=';
	while (val[j])
	{
		str[i + 1 + j] = val[j];
		j++;
	}
	return (str);
}

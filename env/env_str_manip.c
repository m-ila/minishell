/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_manip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:47:17 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/15 16:57:10 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_char_to_null(char **str1, char **str2, char **str3)
{
	if (str1)
		*str1 = NULL;
	if (str2)
		*str2 = NULL;
	if (str3)
		*str3 = NULL;
}

void	ft_multiple_free(char **str1, char **str2, char **str3)
{
	if (str1)
		free(*str1);
	if (str2)
		free(*str2);
	if (str3)
		free(*str3);
	ft_set_char_to_null(str1, str2, str3);
}

char	*ft_get_val_to_search_in_env(t_data *ms, t_cmd *cmds, int from)
{
	int	until;

	if (!ms->b_temoin || !cmds->epured_model || \
	from >= (int) ft_strlen(cmds->epured_model))
		return (ft_strdup(""));
	until = ft_strlen_unbase(cmds->epured_model, "1", from);
	return (ft_strdup_limiters(cmds->raw_str, from, from + until));
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

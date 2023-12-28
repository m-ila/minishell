/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_actual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:40:41 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/23 16:50:08 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* NOT TESTED */
bool	ft_exists_in_env(t_env_node *envi, char *tag_)
{
	if (!envi || !tag_)
		return (false);
	while (envi)
	{
		if (!ft_strncmp(envi->n_tag, tag_, ft_strlen(envi->n_tag)))
			return (true);
		envi = envi->next;
	}
	return (false);
}

/* NOT TESTED */
char	*ft_get_tag_or_cont(char *str, char t_or_c)
{
	int	i;
	int	len;

	if (!str || (t_or_c != 't' && t_or_c != 'c') || !ft_strocc(str, '='))
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	if (t_or_c == 't')
		return (ft_strdup_limiters(str, 0, i));
	else if (t_or_c == 'c' && i != len && i + 1 < len)
		return (ft_strdup_limiters(str, i + 1, ft_strlen(str)));
	else if (t_or_c == 'c' && (i == len || i + 1 == len))
		return (ft_strdup(""));
	return (NULL);
}

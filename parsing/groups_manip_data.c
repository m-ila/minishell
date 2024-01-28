/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_manip_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 14:00:52 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 14:32:18 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	ft_get_token(char *value)
{
	char		*tmp;
	t_tokens	ret;

	if (!value)
		return (error);
	tmp = ft_strdup_limiters(value, 0, ft_strlen_unbase(value, "<>", 0));
	if (!tmp)
		return (error);
	ret = ft_which_redir_token(tmp, 'p');
	ft_multiple_free(&tmp, NULL, NULL);
	return (ret);
}

/*
Will need to be freed, can be NULL
*/
char	*ft_get_file_name(char *value)
{
	int		start;
	int		end;

	start = ft_strlen_unbase(value, "<>", 0) + 1;
	end = ft_strlen(value);
	return (ft_strdup_limiters(value, start, end));
}

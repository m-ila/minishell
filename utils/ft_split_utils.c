/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:19:48 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/25 19:37:45 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_split_entry_exit(char *str)
{
	char	**ret;

	if (!str)
		return (NULL);
	ret = (char **)ft_calloc(1, sizeof(char *));
	if (!ret)
		return (NULL);
	return (ret);
}

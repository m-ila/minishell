/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_sep_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:46:08 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/25 19:36:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* cherche si un des caractere est dans la base */
bool	ft_only_sep_unbase(char *str, char *base)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (ft_char_in_base(str[i], base))
			return (false);
		i++;
	}
	return (true);
}

/* cherche si un des caractere n'est pas dans la base */
bool	ft_only_sep_base(char *str, char *base)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_char_in_base(str[i], base))
			return (false);
		i++;
	}
	return (true);
}

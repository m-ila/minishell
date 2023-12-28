/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_is_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:24:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/25 21:39:36 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\b' || c == '\v' || c == '\f');
}

/* COMMENT : retourne faux si base vide */
int	ft_char_in_base(char c, const char *base)
{
	int	i;

	if (!base || !*base)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

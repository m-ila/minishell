/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:06:55 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/29 13:09:47 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_from(char *str, int from)
{
	int	len_max;

	len_max = ft_strlen(str);
	if (!str || from >= len_max)
		return (0);
	return (len_max - from);
}

/* return the lenght of a substr between and index from 
and the first occ of a base or the end of the str */
int	ft_strlen_base(char *str, char *base, int from)
{
	int	len_max;
	int	len;

	if (!str || !*str || !base || !*base)
		return (0);
	len_max = ft_strlen(str);
	if (from >= len_max)
		return (0);
	len = 0;
	while (from < len_max)
	{
		if (ft_char_in_base(str[from], base))
			return (len);
		if (!ft_char_in_base(str[from], base))
			len++;
		from++;
	}
	return (len);
}

/* return the lenght of a substr between and index from 
and the first occ not included in a base or the end of the str */
int	ft_strlen_unbase(char *str, char *base, int from)
{
	int	len_max;
	int	len;

	if (!str || !*str || !base || !*base)
		return (0);
	len_max = ft_strlen(str);
	if (from >= len_max)
		return (0);
	len = 0;
	while (from < len_max)
	{
		if (!ft_char_in_base(str[from], base))
			return (len);
		if (ft_char_in_base(str[from], base))
			len++;
		from++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:20:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 15:48:12 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_has_only_before(char *s, int i, int (*fun)(char))
{
	int	from;

	if (i >= (int) ft_strlen(s) || i < 0)
		return (false);
	from = 0;
	while (from < i)
	{
		if (!fun(s[from]))
			return (false);
		from++;
	}
	return (true);
}

bool	ft_has_only_after(char *s, int i, int (*fun)(char))
{
	int	from;
	int	len_max;

	len_max = (int) ft_strlen(s);
	if (i >= len_max || i < 0)
		return (false);
	from = i;
	while (from < len_max)
	{
		if (!fun(s[from]))
			return (false);
		from++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:14:20 by mbruyant          #+#    #+#             */
/*   Updated: 2023/10/11 18:14:48 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_sign(char *str, int *i, int *neg)
{
	if (str[*i] == '-')
	{
		(*neg) = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
}

int	ft_isint(char *str)
{
	int			i;
	int			neg;
	long long	nombre;

	i = 0;
	neg = 1;
	nombre = 0;
	if (!str || *str == '\0')
		return (0);
	ft_skip_sign(str, &i, &neg);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '\0')
			return (0);
		while (ft_isdigit(str[i]))
		{
			nombre = (nombre * 10) + (str[i] - '0');
			i++;
			if ((neg == -1 && ((neg * nombre) < INT_MIN)) || \
			(neg == 1 && nombre > INT_MAX))
				return (0);
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:57:46 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/22 11:53:26 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* COMMENT : retourne faux si base vide */
int	ft_char_in_base(char c, const char *base)
{
	int	i;

	if (!base || !*base || !ft_isascii(c))
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

/* looks if all char of str are in a set base */
int	ft_strbase(char *str, const char *base)
{
	int	i;
	int	j;

	i = 0;
	if (!str || !base || *base == 0 || *str == 0)
		return (0);
	while (str[i])
	{
		j = 0;
		while (base[j])
		{
			if (base[j] == str[i])
				break ;
			if (base[j + 1] == '\0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_strindex(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || *str == 0)
		return (-1);
	while (i < (int) ft_strlen(str))
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup_limiters(char *str, int from, int until)
{
	char		*dup;
	int			len;
	int			i;

	if (until > (int) ft_strlen(str) || from >= until || from < 0 || until < 0)
	{
		return (0);
	}
	len = until - from;
	i = 0;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (str[from + i] != '\0' && (from + i < until))
	{
		dup[i] = str[from + i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strocc(char *str, char c)
{
	int	i;
	int	occ;

	if (!str || !ft_isascii(c))
		return (0);
	if (str[0] == '\0' && c == '\0')
		return (1);
	i = 0;
	occ = 0;
	while ((size_t) i < ft_strlen(str))
	{
		if (str[i] == c)
			occ++;
		i++;
	}
	return (occ);
}

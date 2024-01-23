/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:21:43 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/23 11:46:24 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] || s2[i]) && i < n - 1)
		i++;
	if (s1[i] != s2[i] && (n != 0))
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	return (0);
}

char	*ft_strnstr(const char	*big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == 0)
		return ((char *) big);
	if (!big && n == 0)
		return (NULL);
	while (big[i])
	{
		while (big[i + j] == little[j] && ((i + j) < n) && j < n)
		{
			if (little[j + 1] == '\0')
				return ((char *) big + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

bool	ft_russian_str(char *hay, char *needle)
{
	size_t	i;
	size_t	j;
	size_t	len_max;

	if (!hay || !needle)
		return (false);
	i = 0;
	j = 0;
	len_max = ft_strlen(hay);
	while (i + j < len_max)
	{
		j = 0;
		while (hay[i + j] == needle[j] && ((i + j) < len_max))
		{
			if (needle[j + 1] == '\0' && \
			(ft_iswhitespace(hay[i + j + 1]) || i + j + 2 >= len_max))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

/* needs to check if valid args before because size_t doesn't allow error ret */
size_t	ft_russian_index(char *hay, char *needle)
{
	size_t	i;
	size_t	j;
	size_t	len_max;

	i = 0;
	j = 0;
	len_max = ft_strlen(hay);
	while (i + j < len_max)
	{
		j = 0;
		while (hay[i + j] == needle[j] && ((i + j) < len_max))
		{
			if (needle[j + 1] == '\0' && \
			(ft_iswhitespace(hay[i + j + 1]) || i + j + 2 >= len_max))
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

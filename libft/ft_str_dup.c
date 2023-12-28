/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:20:19 by mbruyant          #+#    #+#             */
/*   Updated: 2023/10/11 16:59:09 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		srclen;

	srclen = ft_strlen(s);
	dup = malloc((srclen * sizeof(char)) + 1);
	if (!dup)
		return (0);
	ft_strcpy(dup, s);
	return (dup);
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

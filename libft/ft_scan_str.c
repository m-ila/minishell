/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:40:47 by mbruyant          #+#    #+#             */
/*   Updated: 2023/10/11 17:07:16 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* look in str for a diff char than c, \n and \0 */
int	ft_scanstr(char *str, char c)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (str[++i] && i < len)
		if (str[i] != c && str[i] != '\n')
			return (0);
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return ((char *) s + ft_strlen(s));
	while (s[i] && c != 0)
	{
		if (s[i] == (unsigned char) c)
			return ((char *) s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	i = ft_strlen(s);
	str = (char *) s;
	while (str[i] != (char) c && i != 0)
		i--;
	if (str[i] == (char) c)
		return (str + i);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*retour;
	size_t	i;
	size_t	j;
	size_t	max;

	max = 0;
	while ((start + max) < (unsigned long) ft_strlen(s) && max < len)
		max++;
	retour = (char *) malloc((max + 1) * sizeof(char));
	if (!retour)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		if (i >= start)
		{
			retour[j] = s[i];
			j++;
		}
		i++;
	}
	retour[j] = '\0';
	return (retour);
}

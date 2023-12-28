/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:11:39 by mbruyant          #+#    #+#             */
/*   Updated: 2023/10/11 17:11:08 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!s || !f)
		return ;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*finale;
	size_t	i;
	size_t	j;
	int		total_len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	finale = (char *) ft_calloc((total_len + 1), sizeof(char));
	if (!finale)
		return (NULL);
	while (s1[i] != '\0')
	{
		finale[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		finale[i + j] = s2[j];
		j++;
	}
	return (finale);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*result;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && (ft_strchr(set, *s1) != 0))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len - 1]) != 0)
		len--;
	ret = (char *) ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, len);
	return (ret);
}

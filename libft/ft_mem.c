/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 22:17:09 by mbruyant          #+#    #+#             */
/*   Updated: 2023/10/11 16:53:26 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*buff_s;

	i = 0;
	buff_s = (unsigned char *) s;
	while (i < n)
	{
		if (buff_s[i] == (unsigned char) c)
			return (buff_s + i);
		i++;
	}
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*buff_s1;
	unsigned char	*buff_s2;
	size_t			i;

	i = 0;
	buff_s1 = (unsigned char *) s1;
	buff_s2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (buff_s1[i] != buff_s2[i])
			return (buff_s1[i] - buff_s2[i]);
		i++;
	}
	return (0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*buff_dest;
	unsigned char	*buff_src;
	size_t			i;

	buff_dest = (unsigned char *) dest;
	buff_src = (unsigned char *) src;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			buff_dest[i] = buff_src[i];
			i++;
		}
	}
	if (src < dest)
	{
		while (n > 0)
		{
			buff_dest[n - 1] = buff_src[n - 1];
			n--;
		}
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*strsrc;
	char		*strdest;

	i = 0;
	strsrc = (const char *)src;
	strdest = (char *)dest;
	if ((n == 0) || (src == dest))
		return (dest);
	while (i < n)
	{
		strdest[i] = strsrc[i];
		i++;
	}
	return (dest);
}

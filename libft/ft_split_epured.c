/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_epured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:03:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 19:42:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **s, size_t j)
{
	while (j > 0)
	{
		j--;
		free(s[j]);
	}
	free(s);
	return (NULL);
}

static size_t	ft_wrd_len(char *s, char *m, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && m[len] != c)
		len++;
	return (len);
}

static int	ft_wrd_nb(char *s, char *m, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i] != '\0')
	{	
		while (m[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] != '\0' && m[i] != c)
			i++;
	}
	return (nb);
}

static char	*ft_wrd(char *s, char *m, char c)
{
	char	*ret;
	int		index;

	if (!s)
		return (NULL);
	ret = (char *) malloc((ft_wrd_len(s, m, c) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (m[index] != c && index < (int) ft_strlen(s))
	{
		ret[index] = s[index];
		index++;
	}
	ret[index] = '\0';
	return (ret);
}

char	**ft_split_epured(char *s, char *m, char c)
{
	char		**ret;
	int			j;
	int			i;

	j = 0;
	i = 0;
	if (!s || ft_str_only_sep(m, c))
		return (ft_split_entry_exit( m));
	ret = (char **)ft_calloc((ft_wrd_nb(s, m, c) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && m[i] == c)
			i++;
		if (s[i] != '\0')
		{
			ret[j] = ft_wrd(s, m, c);
			if (!ret[j])
				return (ft_free(ret, j));
			j++;
		}
		while (s[i] != '\0' && m[i] != c)
			i++;
	}
	return (ret);
}

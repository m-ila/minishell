/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_epured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:03:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 21:06:04 by mbruyant         ###   ########.fr       */
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

static size_t	ft_wrd_len(char *s, char *m, char c, int *i)
{
	int	len;

	len = 0;
	while (s[*i + len] != '\0' && m[*i + len] != c)
		len++;
	return (len);
}

static int	ft_wrd_nb(char *s, char *m, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i] != '\0' && m[i])
	{
		while (m[i] && m[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0' && m[i])
			nb++;
		while (s[i] != '\0' && m[i] != c && m[i])
			i++;
	}
	return (nb);
}

static char	*ft_wrd(char *s, char *m, char c, int *i)
{
	char	*ret;
	int		index;

	if (!s)
		return (NULL);
	ret = ft_calloc((ft_wrd_len(s, m, c, i) + 1), sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (m[index + *i] != c && (index + *i) < (int) ft_strlen(s) && \
	(index + *i) < (int) ft_strlen(m))
	{
		ret[index] = s[index + *i];
		index++;
	}
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
		return (ft_split_entry_exit(m));
	ret = (char **)ft_calloc((ft_wrd_nb(s, m, c) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (s[i] != '\0' && m[i])
	{
		ft_split_do_1(s, m, &i, c);
		if (s[i] != '\0')
		{
			ret[j] = ft_wrd(s, m, c, &i);
			if (!ret[j])
				return (ft_free(ret, j));
			j++;
		}
		ft_split_do_2(s, m, &i, c);
	}
	return (ret);
}

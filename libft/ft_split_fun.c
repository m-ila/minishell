/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:03:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 18:37:30 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	still need to norm it and finalize the safety check at the beg of split
*/
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

static size_t	ft_wrd_len(char *s, bool (*fun)(char*, int), int *from)
{
	int	len;

	len = 0;
	while (s[*from + len] != '\0' && fun(s, *from + len) != true)
		len++;
	return (len);
}

static int	ft_wrd_nb(char *s, bool (*fun)(char*, int))
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i] != '\0')
	{	
		while (s[i] != '\0' && fun(s, i))
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] != '\0' && !fun(s, i))
			i++;
	}
	return (nb);
}

static char	*ft_wrd(char *s, bool (*fun)(char*, int), int *from)
{
	char	*ret;
	int		index;

	if (!s || *from >= (int) ft_strlen(s))
		return (NULL);
	ret = (char *) malloc((ft_wrd_len(s, (fun), from) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (*from + index < (int) ft_strlen(s) && !fun(s, *from + index))
	{
		ret[index] = s[*from + index];
		index++;
	}
	ret[index] = '\0';
	return (ret);
}

char	**ft_split_fun(char *s, bool (*fun)(char*, int))
{
	char		**ret;
	int			j;
	int			i;

	j = 0;
	i = 0;
	if (!s || ft_str_only_sep(s, ' '))
		return (ft_split_entry_exit(s));
	ret = (char **)ft_calloc((ft_wrd_nb(s, (fun)) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (s[i] != '\0')
	{
		ft_split_do(s, &i, fun, 1);
		if (s[i] != '\0')
		{
			ret[j] = ft_wrd(s, fun, &i);
			if (!ret[j])
				return (ft_free(ret, j));
			j++;
		}
		i += ft_strlen(ret[j - 1]);
		ft_split_do(s, &i, fun, 2);
	}
	return (ret);
}

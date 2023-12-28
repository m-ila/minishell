/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_unbase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:03:30 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/25 19:41:57 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*split_unbase separe a partir de tous les elem qui ne sont pas dans une base*/
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

static size_t	ft_wrd_len(const char *s, char *base)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && ft_char_in_base(*s, base))
		len++;
	return (len);
}

static int	ft_wrd_nb(const char *s, char *base)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i] != '\0')
	{	
		while (!ft_char_in_base(s[i], base) && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] != '\0' && ft_char_in_base(s[i], base))
			i++;
	}
	return (nb);
}

static char	*ft_wrd(char const *s, char *base)
{
	char	*ret;
	int		index;

	if (!s)
		return (NULL);
	ret = (char *) malloc((ft_wrd_len(s, base) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (ft_char_in_base(s[index], base) && index < (int) ft_strlen(s))
	{
		ret[index] = s[index];
		index++;
	}
	ret[index] = '\0';
	return (ret);
}

char	**ft_split_unbase(char const *s, char *base)
{
	char		**ret;
	int			j;

	j = 0;
	if (!s || ft_only_sep_unbase((char *) s, base))
		return (ft_split_entry_exit((char *) s));
	ret = (char **)ft_calloc((ft_wrd_nb(s, base) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (*s != '\0')
	{
		while (*s != '\0' && !ft_char_in_base(*s, base))
			s++;
		if (*s != '\0')
		{
			ret[j] = ft_wrd(s, base);
			if (!ret[j])
				return (ft_free(ret, j));
			j++;
		}
		while (*s != '\0' && ft_char_in_base(*s, base))
			s++;
	}
	return (ret);
}

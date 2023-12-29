/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:49:06 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/29 20:44:53 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_2d_lines(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	ft_free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_copy_2d_array(char **arr, int from, int len)
{
	int		i;
	char	**ret;

	i = 0;
	if (*arr == 0 || !arr)
		return (NULL);
	ret = ft_calloc(len + 1, sizeof(char *));
	while (arr[i + from] && ((i + from) < len))
	{
		ret[i] = ft_strdup(arr[from + i]);
		i++;
	}
	return (ret);
}

int	ft_len_2d_array(char **arr)
{
	int	len;

	len = 0;
	if (arr[0] == NULL)
		return (0);
	while (arr[len] != NULL)
		len++;
	return (len);
}

int	ft_2d_has_doubles(char **arr)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_len_2d_array(arr);
	while (i + 1 < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (!ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) && \
			!ft_strncmp(arr[i], arr[j], ft_strlen(arr[j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

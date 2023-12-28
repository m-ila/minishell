/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:44:31 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 22:53:32 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_deal_malloc_err(char *str)
{
	ft_printf_fd(2, "%s\n", str);
	return (NULL);
}

char	*ft_str_epur(char *str, char to_remove)
{
	int		i;
	char	*buff;
	char	*result;

	if (!str || !*str || to_remove == '\0' || !ft_strocc(str, to_remove))
		return (ft_strdup(str));
	i = 0;
	buff = ft_calloc(ft_strlen(str) - ft_strocc(str, to_remove) + 1, \
	sizeof(char));
	if (!buff)
		return (ft_deal_malloc_err("malloc fail ft_str_epur"));
	result = buff;
	while (str[i])
	{
		while (str[i] && str[i] == to_remove)
			i++;
		if (str[i])
		{
			*buff = str[i];
			i++;
			buff++;
		}
	}
	return (result);
}

/* arr has to be a previously malloced array !!
so if passing envp as arr, make copy of it or else it will leak */
void	ft_arr_epur(char **arr, char to_remove)
{
	int		i;
	char	*buff;

	if (!arr || !*arr)
		return ;
	if (to_remove == '\0')
		return ((void) \
		ft_deal_malloc_err("incorrect value, arr will not be modified"));
	i = 0;
	while (arr[i])
	{
		buff = arr[i];
		arr[i] = ft_str_epur(buff, to_remove);
		free(buff);
		i++;
	}
}

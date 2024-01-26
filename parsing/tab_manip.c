/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:18:31 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/27 00:05:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_cpy_first_tab(char ***tab1, char ***tab_to, size_t *i)
{
	(*i) = -1;
	while ((*tab1)[++(*i)])
	{
		(*tab_to)[*i] = ft_strdup((*tab1)[*i]);
		if (!(*tab_to)[*i])
		{
			ft_free_2d_array(*tab_to);
			return (false);
		}
	}
	return (true);
}

bool	ft_add_str_to_tab(char ***tab1, char *str)
{
	size_t	len_max;
	size_t	i;
	char	**tab_ret;

	if (!tab1 || !str)
		return (false);
	len_max = ft_2d_lines(*tab1) + 1;
	tab_ret = ft_calloc(len_max + 1, sizeof(char *));
	if (!tab_ret)
		return (false);
	if (!ft_cpy_first_tab(tab1, &tab_ret, &i))
	{
		ft_free_2d_array(tab_ret);
		return (false);
	}		
	tab_ret[i] = ft_strdup(str);
	if (!tab_ret[i])
	{
		ft_free_2d_array(tab_ret);
		return (false);
	}
	ft_free_2d_array(*tab1);
	*tab1 = tab_ret;
	return (true);
}

bool	ft_add_tabs(char ***tab1, char **tab2)
{
	size_t	len_max;
	size_t	i;
	size_t	j;
	char	**tab_ret;

	if (!tab1 || !tab2)
		return (false);
	len_max = ft_2d_lines(*tab1) + ft_2d_lines(tab2);
	tab_ret = ft_calloc(len_max + 1, sizeof(char *));
	if (!tab_ret)
		return (false);
	j = -1;
	if (!ft_cpy_first_tab(tab1, &tab_ret, &i))
	{
		ft_free_2d_array(tab_ret);
		return (false);
	}	
	while (tab2[++j])
	{
		tab_ret[i + j] = ft_strdup(tab2[j]);
		if (!tab_ret[i + j])
		{
			ft_free_2d_array(tab_ret);
			return (false);
		}
	}
	ft_free_2d_array(*tab1);
	*tab1 = tab_ret;
	return (true);
}

/*
int main(int argc, char **argv, char **envp)
{
	char 	**cpy;
	char	**to_add;
	int		i = -1;

	if (argc > 3 && envp)
	{
		printf("test : %s\n\n", envp[1]);
		cpy = ft_copy_2d_array(argv, 1, 4);
		to_add = ft_copy_2d_array(envp, 1, 13);
		if (!cpy || !to_add)
			printf("bof\n\n\n");
		ft_add_tabs(&cpy, to_add);
		while (cpy[++i])
			printf("cpy[%d] : %s\n", i, cpy[i]);
		printf("\n\ntest2\n");
		ft_add_str_to_tab(&cpy, "coucou les amis !");
		i = -1;
		while (cpy[++i])
			printf("cpy[%d] : %s\n", i, cpy[i]);
		ft_free_2d_array(cpy);
		ft_free_2d_array(to_add);
	}
	return (0);
}
*/

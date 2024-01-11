/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_split_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:19:37 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/11 13:32:13 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	**tab;
	char    **tab1;
	char    **tab2;
	char    **tab3;
	char    *str = "\'coucou\' les \"amis\"";
	char    *str1 = "chaine de char classique";
	char    *str2 = "\"c\'est la vie\" fin";
	char    *str3 = "";
	int     j = 0;
	
	tab = ft_split_fun(str, ft_char_is_a_reigning_quote);
	if (!tab)
		return (ft_printf_fd(2, "nope\n"));
	tab1 = ft_split_fun(str1, ft_char_is_a_reigning_quote);
	if (!tab1)
		return (ft_printf_fd(2, "nope\n"));
	tab2 = ft_split_fun(str2, ft_char_is_a_reigning_quote);
	if (!tab2)
		return (ft_printf_fd(2, "nope\n"));
	tab3 = ft_split_fun(str3, ft_char_is_a_reigning_quote);
	if (!tab3)
		return (ft_printf_fd(2, "nope\n"));
	ft_printf_fd(1, "tab\n");
	while (tab[j])
	{
		ft_printf_fd(1, "elem n.%d = %s\n", j, tab[j]);
		j++;
	}
	j = 0;
	ft_printf_fd(1, "\ntab1\n");
	while (tab1[j])
	{
		ft_printf_fd(1, "elem n.%d = %s\n", j, tab1[j]);
		j++;
	}
	j = 0;
	ft_printf_fd(1, "\ntab2\n");
	while (tab2[j])
	{
		ft_printf_fd(1, "elem n.%d = %s\n", j, tab2[j]);
		j++;
	}
	j = 0;
	ft_printf_fd(1, "\ntab3\n");
	while (tab3[j])
	{
		ft_printf_fd(1, "elem n.%d = %s\n", j, tab3[j]);
		j++;
	}
	ft_free_2d_array(tab);
	ft_free_2d_array(tab1);
	ft_free_2d_array(tab2);
	ft_free_2d_array(tab3);
	return (0);
}

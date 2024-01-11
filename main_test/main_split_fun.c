/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_split_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:19:37 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/11 18:26:26 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_cond_cut(char *str, int i)
{
	if (ft_char_is_a_reigning_quote(str, i))
		return (true);
	if (ft_char_in_base(str[i], BASE_QUOTES) && \
	!ft_elem_is_in_quotes(str, i))
		return (true);
	return (false);
}

int	main(void)
{
	char	**tab;
	char    **tab1;
	char    **tab2;
	char    **tab3;
	char    *str = "\'coucou\' les \"amis\"";
	char    *str1 = "chaine de char classique";
	char    *str2 = "\"c\'est la vie\" fin";
	char    *str3 = "\"\"\'\'echo hola\"\"\'\'\'\' que\"\"\'\' tal\"\"\'\' a";
	int     j = 0;
	
	tab = ft_split_fun(str, ft_cond_cut);
	if (!tab)
		return (ft_printf_fd(2, "nope\n"));
	tab1 = ft_split_fun(str1, ft_cond_cut);
	if (!tab1)
		return (ft_printf_fd(2, "nope\n"));
	tab2 = ft_split_fun(str2, ft_cond_cut);
	if (!tab2)
		return (ft_printf_fd(2, "nope\n"));
	tab3 = ft_split_fun(str3, ft_cond_cut);
	if (!tab3)
		return (ft_printf_fd(2, "nope\n"));
	ft_printf_fd(1, "tab\nstr passee : %s\n", str);
	while (tab[j])
	{
		ft_printf_fd(1, "elem n.%d = (deb)%s(fin)\n", j, tab[j]);
		j++;
	}
	j = 0;
	ft_printf_fd(1, "\ntab1\nstr passee : %s\n", str1);
	while (tab1[j])
	{
		ft_printf_fd(1, "elem n.%d = (deb)%s(fin)\n", j, tab1[j]);
		j++;
	}
	j = 0;
	ft_printf_fd(1, "\ntab2\nstr passee : %s\n", str2);
	while (tab2[j])
	{
		ft_printf_fd(1, "elem n.%d = (deb)%s(fin)\n", j, tab2[j]);
		j++;
	}
	j = 0;
	ft_printf_fd(1, "\ntab3\nstr passee : %s\n", str3);
	while (tab3[j])
	{
		ft_printf_fd(1, "elem n.%d = (deb)%s(fin)\n", j, tab3[j]);
		j++;
	}
	ft_free_2d_array(tab);
	ft_free_2d_array(tab1);
	ft_free_2d_array(tab2);
	ft_free_2d_array(tab3);
	return (0);
}

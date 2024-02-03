/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:57:43 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 16:59:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_invalid_end_token(t_data *ms, char *str)
{
	char	*tmp;

	if (ft_strlen(str) == 1)
	{
		tmp = ft_strdup_limiters(str, 0, 1);
		if (!tmp)
			return (ft_msg("malloc fail invalid end token", 'm', false, ms));
		ft_print_msg(tmp, 's', 0, ms);
		ft_multiple_free(&tmp, NULL, NULL);
		return ;
	}
	if (ft_strlen(str) == 2 && str[0] != str[1])
	{
		tmp = ft_strdup_limiters(str, 1, 2);
		if (!tmp)
			return (ft_msg("malloc fail invalid end token", 'm', false, ms));
		ft_print_msg(tmp, 's', 0, ms);
		ft_multiple_free(&tmp, NULL, NULL);
		return ;
	}
	ft_print_invalid_token(ms, str);
}

void	ft_print_invalid_start_token(t_data *ms, char *str)
{
	if (str[0] == '|' || str[1] == '|')
	{
		ft_print_msg("|", 's', 0, ms);
		return ;
	}
	ft_print_invalid_token(ms, str);
}

void	ft_print_invalid_token(t_data *ms, char *str)
{
	int		from;
	int		until;
	char	c;
	int		i;
	char	*to_print;

	if (str[0] != str[1] || str[0] == '|' || str[1] == '|')
		from = 1;
	if (str[0] == str[1] && str[0] != '|')
		from = 2;
	until = from;
	i = 0;
	c = str[from];
	while (until < (int) ft_strlen(str) && str[until] == c && i < 2)
	{
		until++;
		if (c == '|')
			break ;
		i++;
	}
	to_print = ft_strdup_limiters(str, from, until);
	ft_print_msg(to_print, 's', 0, ms);
	ft_multiple_free(&to_print, NULL, NULL);
}

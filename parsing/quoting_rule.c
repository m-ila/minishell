/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_rule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:10 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/11 10:34:06 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_return_qu_val(char reigning_quote, int nb_quotes)
{
	if (reigning_quote == '\'' && nb_quotes % 2 != 0)
		return (SINGLE_QUOTED);
	if (reigning_quote == '\"' && nb_quotes % 2 != 0)
		return (DOUBLE_QUOTED);
	if (nb_quotes % 2 == 0)
		return (NOT_QUOTED);
	return (-1);
}

/*
commentaire : si l'element i est une quote, on fait quoi ?
est-ce qu'il serait pas wise de check jusqu'a start == i ?
*/
int	ft_elem_is_in_quotes(char *str, int i)
{
	char	reigning_quote;
	int		nb_reigning_quotes;
	int		nb_quotes;
	int		start;

	if (!str || i >= (int) ft_strlen(str))
		return (-1);
	reigning_quote = '.';
	nb_reigning_quotes = 0;
	nb_quotes = 0;
	start = 0;
	while (str[start] && start < i)
	{
		if (ft_char_in_base(str[start], BASE_QUOTES) && \
		str[start] != reigning_quote && nb_quotes % 2 == 0)
		{
			reigning_quote = str[start];
			nb_reigning_quotes++;
			nb_quotes = 0;
		}
		if (str[start] == reigning_quote)
			nb_quotes++;
		start++;
	}
	return (ft_return_qu_val(reigning_quote, nb_quotes));
}

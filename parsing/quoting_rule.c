/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_rule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:10 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/11 19:08:40 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_assign_char(char *s, int i, char *model)
{
	if (s[i] == '$' && ft_elem_is_in_quotes(s, i) == SINGLE_QUOTED)
		model[i] = 'e';
	else if (ft_iswhitespace(s[i]))
		model[i] = 's';
	else if (ft_char_in_base(s[i], BASE_QUOTES))
		model[i] = 'q';
	else
		model[i] = '1';
}

char	*ft_epured_model(char *s)
{
	char	*model;
	int		i;

	if (!s)
		return (ft_strdup(""));
	model = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!model)
		return (ft_strdup(""));
	i = 0;
	while (s[i])
	{
		if (!ft_cond_cut(s, i))
			ft_assign_char(s, i, model);
		if (ft_cond_cut(s, i))
			model[i] = '0';
		i++;
	}
	return (model);
}

bool	ft_cond_cut(char *str, int i)
{
	if (ft_char_is_a_reigning_quote(str, i))
		return (true);
	if (ft_char_in_base(str[i], BASE_QUOTES) && \
	!ft_elem_is_in_quotes(str, i))
		return (true);
	return (false);
}

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
	int		nb_quotes;
	int		start;

	if (!str || i >= (int) ft_strlen(str))
		return (-1);
	reigning_quote = '.';
	nb_quotes = 0;
	start = 0;
	while (str[start] && start < i)
	{
		if (ft_char_in_base(str[start], BASE_QUOTES) && \
		str[start] != reigning_quote && nb_quotes % 2 == 0)
		{
			reigning_quote = str[start];
			nb_quotes = 0;
		}
		if (str[start] == reigning_quote)
			nb_quotes++;
		start++;
	}
	return (ft_return_qu_val(reigning_quote, nb_quotes));
}

bool    ft_char_is_a_reigning_quote(char *str, int i)
{
    char	reigning_quote;
	int		nb_quotes;
	int		start;

	if (!str || i >= (int) ft_strlen(str) || \
    !ft_char_in_base(str[i], BASE_QUOTES))
		return (false);
	reigning_quote = '.';
	nb_quotes = 0;
	start = 0;
	while (str[start] && start < i)
	{
		if (ft_char_in_base(str[start], BASE_QUOTES) && \
		str[start] != reigning_quote && nb_quotes % 2 == 0)
		{
			reigning_quote = str[start];
			nb_quotes = 0;
		}
		if (str[start] == reigning_quote)
			nb_quotes++;
		start++;
	}
    if (str[i] == reigning_quote && nb_quotes % 2 != 0)
        return (true);
    return (false);
}

/*
commentaire : shouldn't it be from >= ft_strlen - 1 since
                                        until = from + 1 ?
to be tested later
*/
int ft_get_index_next_reign_quo(char *str, int from)
{
    int until;

    if (!str || from >= (int) ft_strlen(str))
        return (NO_INDEX_FOUND);
    until = from + 1;
    while (str[until] && !ft_char_is_a_reigning_quote(str, until))
        until++;
    return (until);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:39:50 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 16:01:47 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Basically returns the value of an "until" for a substr
returns -1 in case of error
*/
int	get_index_next_token(char *str, int from)
{
	int		occ_rule;
	char	quoting_rule;

	if (from >= (int) ft_strlen(str) || from < 0 || !str)
		return (-1);
	quoting_rule = '.';
	occ_rule = 0;
	while (str[from])
	{
		if (ft_char_in_base(str[from], BASE_QUOTES))
		{
			if (quoting_rule == '.')
				quoting_rule = str[from];
			if (str[from] == quoting_rule)
				occ_rule++;
		}
		if (ft_char_in_base(str[from], BASE_TOKEN) && occ_rule % 2 == 0)
			return (from);
		from++;
	}
	if (from == (int) ft_strlen(str))
		return (from);
	return (-1);
}

/* retourne la str correspondant a une cmd */
char	*get_cmd(char *str, int from)
{
	int		until;

	if (!str || from < 0 || from >= (int) ft_strlen(str))
		return (NULL);
	until = get_index_next_token(str, from);
	if (until == -1 || until < from)
		return (ft_char_print_msg("getting until index", 'm', NULL, NULL));
	return (ft_strdup_limiters(str, from, until));
}

/* retourne la str correspondant a une redirection */
char	*get_token(char *str, int from)
{
	if (!str || from < 0 || from > (int) ft_strlen(str))
		return (NULL);
	if (from == (int) ft_strlen(str))
		return (ft_strdup(""));
	return (ft_strdup_limiters(str, from, \
	from + ft_strlen_unbase(str, BASE_TOKEN, from)));
}

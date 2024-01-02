/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:31:51 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/02 17:44:05 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Basically returns the value of an "until" for a substr
returns -1 in case of error
*/
int	get_next_token(char *str, int from)
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

int	main(int argc, char **argv)
{
	int		index;
	int		until;
	char	*tmp;

	index = 0;
	until = 0;
	if (argc)
	{
		while (index < (int) ft_strlen(argv[1]))
		{
			until = get_next_token(argv[1], index);
			tmp = ft_strdup_limiters(argv[1], index, until);
			ft_printf_fd(1, "index : %d\nuntil : %d\nsubchar : %s\n", \
			index, until, tmp);
			index = until;
			while (ft_char_in_base(argv[1][index], BASE_TOKEN))
				index++;
			free(tmp);
		}
	}
	return (0);
}

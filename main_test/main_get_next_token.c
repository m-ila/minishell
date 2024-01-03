/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:31:51 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/03 14:05:57 by mbruyant         ###   ########.fr       */
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

char	*get_cmd(char *str, int *from)
{
	int		occ_rule;
	char	quoting_rule;
	
	if (*from >= (int) ft_strlen(str) || *from < 0 || !str)
		return (ft_strdup(""));
	quoting_rule = '.';
	occ_rule = 0;
	while (str[*from])
	{
		if (ft_char_in_base(str[*from], BASE_QUOTES))
		{
			if (quoting_rule == '.')
				quoting_rule = str[*from];
			if (str[*from] == quoting_rule)
				occ_rule++;
		}
		if (ft_char_in_base(str[*from], BASE_TOKEN) && occ_rule % 2 == 0)
			return (ft_strdup_limiters(str, *from, *from + ft_strlen_base(str, BASE_TOKEN, *from)));
		(*from)++;
	}
	if (*from == (int) ft_strlen(str))
	{
		if (occ_rule % 2 == 0)
			return (ft_strdup_limiters(str, *from, ft_strlen_from(str, *from)));
		else
			return (ft_char_print_msg("quoting_rule", 's', ft_strdup(""), NULL));
	}
	return (ft_strdup(""));
}

char	*get_token(char *str, int *from)
{
	int		occ_rule;
	char	quoting_rule;
	
	if (*from >= (int) ft_strlen(str) || *from < 0 || !str)
		return (ft_strdup(""));
	quoting_rule = '.';
	occ_rule = 0;
	while (str[*from])
	{
		if (ft_char_in_base(str[*from], BASE_QUOTES))
		{
			if (quoting_rule == '.')
				quoting_rule = str[*from];
			if (str[*from] == quoting_rule)
				occ_rule++;
		}
		if (ft_char_in_base(str[*from], BASE_TOKEN) && occ_rule % 2 == 0)
			return (ft_strdup_limiters(str, *from, *from + ft_strlen_unbase(str, BASE_TOKEN, *from)));
		(*from)++;
	}
	if (*from == (int) ft_strlen(str))
		return (ft_strdup_limiters(str, *from, ft_strlen_from(str, *from)));
	return (ft_strdup(""));
}

int	main(int argc, char **argv)
{
	int		index;
//	int		until;
	char	*tmp;
	char	*tmp_t;

	index = 0;
//	until = 0;
	if (argc)
	{
		if (ft_starts_with_token(argv[1]))
		{
			while (ft_iswhitespace(argv[1][index]))
				index++;
			tmp_t = get_token(argv[1], &index);
			if (!ft_is_valid_entry_token(tmp_t))
				ft_printf_fd(1, "invalid entry token\n");
			free(tmp_t);
		}
		while (index < (int) ft_strlen(argv[1]) - 1)
		{
			tmp = get_cmd(argv[1], &index);
			ft_printf_fd(1, "cmd : %s\n", tmp);
			tmp_t = get_token(argv[1], &index);
			ft_printf_fd(1, "token : %s\n", tmp_t);
		}
	}
	return (0);
}

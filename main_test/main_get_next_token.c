/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:31:51 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/03 17:06:11 by mbruyant         ###   ########.fr       */
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

char	*get_token(char *str, int from)
{
	if (!str || from < 0 || from > (int) ft_strlen(str))
		return (NULL);
	if (from == (int) ft_strlen(str))
		return (ft_strdup(""));
	return (ft_strdup_limiters(str, from, from + ft_strlen_unbase(str, BASE_TOKEN, from)));
}

/* to include t_data *ms so it can print the printed line */
int	deal_with_token(char *str, char *tok_str, int from)
{
	int		ret;

	if (from + (int) ft_strlen(tok_str) == (int) ft_strlen(str))
		return (1);
	if (!str || !tok_str || tok_str[0] == '\0' || from < 0 || from >= (int) ft_strlen(str))
		return (0);
	if (!ft_is_valid_token(tok_str))
		ret = ft_print_msg(tok_str, 'm', 0, NULL);
	if (ft_is_valid_token(tok_str))
		ret = 1;
	return (ret);
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
			tmp_t = get_token(argv[1], index);
			if (!ft_is_valid_entry_token(tmp_t))
				ft_printf_fd(1, "invalid entry token\n");
			index += (int) ft_strlen(tmp_t);
			free(tmp_t);
		}
		while (index < (int) ft_strlen(argv[1]))
		{
			tmp = get_cmd(argv[1], index);
			if (!tmp)
				return (ft_print_msg("get_cmd issue", 'm', 0, NULL));
			ft_printf_fd(1, "cmd : '%s'\nfrom : %d\nuntil : %d\n", tmp, index, index + ft_strlen(tmp));
			if (tmp)
				index += (int) ft_strlen(tmp);
			free(tmp);
			ft_printf_fd(1, "%s\nfree tmp success\n%s\n", PRINT_SEP, PRINT_SEP);
			tmp_t = get_token(argv[1], index);
			if (!tmp_t)
				return (ft_print_msg("get_token issue", 'm', 0, NULL));
			ft_printf_fd(1, "%s\ntok : '%s'\nfrom : %d\nuntil : %d\n", PRINT_SEP,tmp_t, index, index + ft_strlen(tmp_t));
			if (!deal_with_token(argv[1], tmp_t, index))
			{
				free(tmp_t);
				return (0);
			}
			if (tmp_t)
				index += (int) ft_strlen(tmp_t);
			free(tmp_t);
		}
		
	}
	return (0);
}

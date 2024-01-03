/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:31:51 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/03 13:31:13 by mbruyant         ###   ########.fr       */
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

int		b_deal_w_token(char *str, int from)
{
	char	*tmp;

	if (from > (int) ft_strlen(str) || from < 0)
		return (0);
	if (from == (int) ft_strlen(str))
		return (0);
	tmp = ft_strdup_limiters(str, from, from + ft_strlen_unbase(str, BASE_TOKEN, from));
	if (!tmp)
		return (ft_print_msg("issue gen tmp val in b_deal_w_token", 'm', 0, NULL));
	if (!ft_is_valid_token(tmp))
	{	
		ft_msg_end(tmp, 's', false, NULL);
		free(tmp);
		return (0);
	}
	return (1);
}

char	*deal_w_token(char *str, int from)
{
	char	*tmp;


	tmp = ft_strdup_limiters(str, from, from + ft_strlen_unbase(str, BASE_TOKEN, from));
	if (!tmp)
		return (ft_char_print_msg("issue gen tmp val in deal_w_token", 'm', NULL, NULL));
	if (!ft_is_valid_token(tmp))
	{	
		ft_msg_end(tmp, 's', false, NULL);
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

int	main(int argc, char **argv)
{
	int		index;
	int		until;
	char	*tmp;
	char	*tmp_t;

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
			tmp_t = ft_strdup_limiters(argv[1], index, index + ft_strlen_unbase(argv[1], BASE_TOKEN, index));
			if (b_deal_w_token(argv[1], index))
			{
				ft_printf_fd(1, "substr t : %s\n", tmp_t);
				index += (int) ft_strlen(tmp_t);
				free(tmp_t);
			}
			if (!b_deal_w_token(argv[1], index))
				return (ft_print_msg("invalid token", 'm', 0, NULL));
			free(tmp);
		}
	}
	return (0);
}

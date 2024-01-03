/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:31:51 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/03 17:37:54 by mbruyant         ###   ########.fr       */
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
	return (ft_strdup_limiters(str, from, from + ft_strlen_unbase(str, BASE_TOKEN, from)));
}

/*
to include t_data *ms so it can print the printed line
check la validite de la str de redirection
*/
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

/*to add t_data *ms to create node from here */
bool	ft_parsing_cmd_process(char *user_input, int *from)
{
	char	*tmp;

	ft_printf_fd(1, "%s\nEntering ft_parsing_cmd_process\n\n", PRINT_SEP);
	tmp = get_cmd(user_input, *from);
	if (!tmp)
		return ((bool) ft_print_msg("get_cmd issue", 'm', 0, NULL));
	ft_printf_fd(1, "cmd : '%s'\nfrom : %d\nuntil : %d\n", tmp, *from, *from + ft_strlen(tmp));
	if (tmp)
		(*from) += (int) ft_strlen(tmp);
	free(tmp);
	ft_printf_fd(1, "%s\nLeaving ft_parsing_cmd_process\n\n", PRINT_SEP);
	return (true);
}

/*to add t_data *ms to create node from here */
bool	ft_parsing_token_process(char *user_input, int *from)
{
	char	*tmp_t;

	tmp_t = get_token(user_input, *from);
	if (!tmp_t)
		return ((bool) ft_print_msg("get_token issue", 'm', 0, NULL));
	ft_printf_fd(1, "%s\nEntering ft_parsing_token_process\n\n", PRINT_SEP);
	ft_printf_fd(1, "tok : '%s'\nfrom : %d\nuntil : %d\n", tmp_t, *from, *from + ft_strlen(tmp_t));
	if (!deal_with_token(user_input, tmp_t, *from))
	{
		free(tmp_t);
		return (false);
	}
	if (tmp_t)
		(*from) += (int) ft_strlen(tmp_t);
	free(tmp_t);
	ft_printf_fd(1, "%s\nLeaving ft_parsing_token_process\n\n", PRINT_SEP);
	return (true);
}

bool	ft_parsing_start_token_process(char *user_input, int *from)
{
	char	*tmp_t;

	while (ft_iswhitespace(user_input[*from]))
		(*from)++;
	tmp_t = get_token(user_input, *from);
	ft_printf_fd(1, "%s\nEntering ft_parsing_start_token_process\n\n", PRINT_SEP);
	ft_printf_fd(1, "tok : '%s'\nfrom : %d\nuntil : %d\n", tmp_t, *from, *from + ft_strlen(tmp_t));
	if (!ft_is_valid_entry_token(tmp_t))
	{
		ft_printf_fd(1, "invalid entry token\n");
		return (false);
	}
	(*from) += (int) ft_strlen(tmp_t);
	free(tmp_t);
	ft_printf_fd(1, "%s\nLeaving ft_parsing_start_token_process\n\n", PRINT_SEP);
	return (true);
}

int	main(int argc, char **argv)
{
	int		index;
	bool	temoin;

	index = 0;
	temoin = true;
	if (argc)
	{
		if (ft_starts_with_token(argv[1]))
			temoin = ft_parsing_start_token_process(argv[1], &index);
		while (index < (int) ft_strlen(argv[1]) && temoin)
		{
			temoin = ft_parsing_cmd_process(argv[1], &index);
			if (temoin)
				temoin = ft_parsing_token_process(argv[1], &index);
		}
	}
	return (0);
}

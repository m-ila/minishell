/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:07:28 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/03 21:13:20 by mbruyant         ###   ########.fr       */
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
int	deal_with_token(char *str, char *tok_str, int from, t_data *ms)
{
	int		ret;

	if (from + (int) ft_strlen(tok_str) == (int) ft_strlen(str))
		return (1);
	if (!str || !tok_str || tok_str[0] == '\0' || from < 0 || from >= (int) ft_strlen(str))
		return (0);
	if (!ft_is_valid_token(tok_str))
		ret = ft_print_msg(tok_str, 's', 0, ms);
	else
		ret = 1;
	return (ret);
}

/*to add t_data *ms to create node from here */
bool	ft_parsing_cmd_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp;
	t_cmd	*buff;

	ft_printf_fd(1, "%s\nEntering ft_parsing_cmd_process\n\n", PRINT_SEP);
	tmp = get_cmd(user_input, *from);
	if (!tmp)
		return ((bool) ft_print_msg("get_cmd issue", 'm', 0, ms));
	buff = ft_create_cmd_node(tmp);
	if (ms->parse_struct->struct_cmds == NULL)
		ms->parse_struct->struct_cmds = buff;
	else
		ft_add_node_to_cmds(&ms->parse_struct->struct_cmds, buff);
	ft_printf_fd(1, "cmd : '%s'\nfrom : %d\nuntil : %d\n", tmp, *from, *from + ft_strlen(tmp));
	if (tmp)
		(*from) += (int) ft_strlen(tmp);
	free(tmp);
	ft_printf_fd(1, "%s\nLeaving ft_parsing_cmd_process\n\n", PRINT_SEP);
	return (true);
}

/*to add t_data *ms to create node from here */
bool	ft_parsing_token_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp_t;

	tmp_t = get_token(user_input, *from);
	if (!tmp_t)
		return ((bool) ft_print_msg("get_token issue", 'm', 0, ms));
	ft_printf_fd(1, "%s\nEntering ft_parsing_token_process\n\n", PRINT_SEP);
	ft_printf_fd(1, "tok : '%s'\nfrom : %d\nuntil : %d\n", tmp_t, *from, *from + ft_strlen(tmp_t));
	if (!deal_with_token(user_input, tmp_t, *from, ms))
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

bool	ft_parsing_start_token_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp_t;

	while (ft_iswhitespace(user_input[*from]))
		(*from)++;
	tmp_t = get_token(user_input, *from);
	ft_printf_fd(1, "%s\nEntering ft_parsing_start_token_process\n\n", PRINT_SEP);
	ft_printf_fd(1, "tok : '%s'\nfrom : %d\nuntil : %d\n", tmp_t, *from, *from + ft_strlen(tmp_t));
	if (!ft_is_valid_entry_token(tmp_t))
	{
		ft_print_msg(tmp_t, 's', 0, ms);
		free(tmp_t);
		return (false);
	}
	(*from) += (int) ft_strlen(tmp_t);
	free(tmp_t);
	ft_printf_fd(1, "%s\nLeaving ft_parsing_start_token_process\n\n", PRINT_SEP);
	return (true);
}

void	ft_raw_parsing_process(char *user_input, t_data *ms)
{
	int		index;
	bool	temoin;
	t_cmd	*cmd_struct;

	index = 0;
	temoin = true;
	cmd_struct = NULL;
	ms->parse_struct->struct_cmds = cmd_struct;
	if (ft_starts_with_token(user_input))
		temoin = ft_parsing_start_token_process(user_input, &index, ms);
	while (index < (int) ft_strlen(user_input) && temoin)
	{
		temoin = ft_parsing_cmd_process(user_input, &index, ms);
		if (temoin)
			temoin = ft_parsing_token_process(user_input, &index, ms);
	}
}

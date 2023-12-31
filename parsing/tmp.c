/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:07:28 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/04 13:32:16 by mbruyant         ###   ########.fr       */
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
print syntax error if there's a false token and change ms->b_temoin to false
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
	{
		ret = ft_print_msg(tok_str, 's', 0, ms);
		ms->b_temoin = false;
	}
	else
		ret = 1;
	return (ret);
}

/*
to add : strdup protection !
*/
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
	{
		ms->parse_struct->struct_cmds = buff;
		buff->prev_token = ft_strdup(ms->tmp_str);
	}
	else
		ft_add_node_to_cmds(&ms->parse_struct->struct_cmds, buff);
	ft_printf_fd(1, "cmd : '%s'\nfrom : %d\nuntil : %d\n", tmp, *from, *from + ft_strlen(tmp));
	if (tmp)
		(*from) += (int) ft_strlen(tmp);
	free(tmp);
	ft_printf_fd(1, "%s\nLeaving ft_parsing_cmd_process\n\n", PRINT_SEP);
	return (true);
}

/*
commentaire
wouldn't be an int more interesting for those function ?
in case of an error, would return proper return value, or else change var_g
*/
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
	if (!ft_add_next_token_to_node(tmp_t, ms->parse_struct->struct_cmds))
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

/*
to do : add strdup protection
*/
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
		ms->b_temoin = false;
		ft_print_msg(tmp_t, 's', 0, ms);
		free(tmp_t);
		return (false);
	}
	free(ms->tmp_str);
	ms->tmp_str = ft_strdup(tmp_t);
	(*from) += (int) ft_strlen(tmp_t);
	free(tmp_t);
	ft_printf_fd(1, "%s\nLeaving ft_parsing_start_token_process\n\n", PRINT_SEP);
	return (true);
}

bool	ft_add_prev_token_to_node(t_cmd *struct_cmd, t_data *ms)
{
	t_cmd	*tmp;

	if (!struct_cmd || !ms)
		return (false);
	if (!struct_cmd->next)
	{
		if (ms->tmp_str != NULL)
			struct_cmd->prev_token = ms->tmp_str;
		return (true);
	}
	if (!ft_add_first_prev_token_node(ms->tmp_str, struct_cmd))
		return (false);
	tmp = struct_cmd->next;
	while (tmp)
	{
		tmp->prev_token = tmp->prev->next_token;
		tmp = tmp->next;
	}
	return (true);
}

/* if not, starts by stdin */
bool	ft_add_first_prev_token_node(char *str, t_cmd *struct_cmd)
{
	if (!struct_cmd)
		return (false);
	if (!str)
		return (true);
	struct_cmd->prev_token = ft_strdup(str);
	free(str);
	str = NULL;
	return (true);
}

bool	ft_add_next_token_to_node(char *str, t_cmd *struct_cmd)
{
	t_cmd	*last;

	if (!struct_cmd || !str)
		return (false);
	last = ft_go_to_last_cmd_node(struct_cmd);
	last->next_token = ft_strdup(str);
	return (true);	
}

/*
to do :
Need to modify the functions starting by temoin = qqch to not start if temoin false
*/
void	ft_raw_parsing_process(char *user_input, t_data *ms)
{
	int		index;
	bool	temoin;
	t_cmd	*cmd_struct;

	index = 0;
	temoin = true;
	cmd_struct = NULL;
	ms->parse_struct->struct_cmds = cmd_struct;
	ms->tmp_str = ft_strdup("");
	if (ft_starts_with_token(user_input))
		temoin = ft_parsing_start_token_process(user_input, &index, ms);
	while (index < (int) ft_strlen(user_input) && temoin)
	{
		temoin = ft_parsing_cmd_process(user_input, &index, ms);
		if (temoin)
			temoin = ft_parsing_token_process(user_input, &index, ms);
	}
	if (cmd_struct && temoin)
	{
		temoin = ft_add_prev_token_to_node(ms->parse_struct->struct_cmds, ms);
		temoin = ft_add_token_val_to_struct(ms->parse_struct->struct_cmds);
	}
}

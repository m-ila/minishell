/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:07:28 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 14:57:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
print syntax error if there's a false token and change ms->b_temoin to false
check la validite de la str de redirection
*/
int	deal_with_token(char *str, char *tok_str, int from, t_data *ms)
{
	int		ret;

	if (from + (int) ft_strlen(tok_str) == (int) ft_strlen(str))
		return (1);
	if (!str || !tok_str || tok_str[0] == '\0' || from < 0 || \
	from >= (int) ft_strlen(str))
		return (0);
	if (!ft_is_valid_token(tok_str))
	{
		ft_print_invalid_token(ms, tok_str);
		ret = 0;
		ms->b_temoin = false;
	}
	else
		ret = 1;
	return (ret);
}

/*
to do : strdup protection !
*/
bool	ft_parsing_cmd_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp;
	t_node	*buff;

	tmp = get_cmd(user_input, *from);
	if (!tmp)
		return (ft_print_msg("get_cmd issue", 'm', false, ms));
	buff = ft_create_cmd_node(tmp);
	if (ms->parse_s->c == NULL)
	{
		ms->parse_s->c = buff;
		buff->prev_tok = ft_strdup(ms->tmp_str);
		if (!buff->prev_tok)
		{
			ms->b_temoin = false;
			return (false);
		}
		buff->tok_prv_tok = ft_which_redir_token(buff->prev_tok, 'p');
		buff->b_is_file = ft_prev_is_red_io(buff);
	}
	else
		ft_add_node_to_cmds(&ms->parse_s->c, buff);
	if (tmp)
		(*from) += (int) ft_strlen(tmp);
	free(tmp);
	return (true);
}

bool	ft_parsing_token_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp_t;

	tmp_t = get_token(user_input, *from);
	if (!tmp_t)
		return (ft_print_msg("get_token issue", 'm', false, ms));
	if (!deal_with_token(user_input, tmp_t, *from, ms))
		return (ft_free_return(&tmp_t, NULL, NULL, false));
	if (!ft_add_next_token_to_node(tmp_t, ms->parse_s->c))
		return (ft_free_return(&tmp_t, NULL, NULL, false));
	if (tmp_t)
		(*from) += (int) ft_strlen(tmp_t);
	return (ft_free_return(&tmp_t, NULL, NULL, true));
}

/*
to do : add strdup protection
if tmp_t[0] == '|', straight up |
*/
bool	ft_parsing_start_token_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp_t;

	while (ft_iswhitespace(user_input[*from]))
		(*from)++;
	tmp_t = get_token(user_input, *from);
	if (!ft_is_valid_entry_token(tmp_t))
	{
		ms->b_temoin = false;
		ft_print_invalid_start_token(ms, tmp_t);
		free(tmp_t);
		return (false);
	}
	ft_multiple_free(&ms->tmp_str, NULL, NULL);
	ms->tmp_str = ft_strdup(tmp_t);
	(*from) += (int) ft_strlen(tmp_t);
	free(tmp_t);
	if (*from >= (int) ft_strlen(user_input) - 1 || \
	ft_has_only_after(user_input, *from, ft_iswhitespace))
	{
		ft_msg("newline", 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}

	return (true);
}

void	ft_raw_parsing_process(char *user_input, t_data *ms)
{
	int		index;
	bool	temoin;
	t_node	*c;
	t_node	*last;

	index = 0;
	temoin = true;
	c = NULL;
	ms->parse_s->c = c;
	if (!user_input)
		return ;
	ms->tmp_str = ft_strdup("");
	if (ft_starts_with_token(user_input))
		temoin = ft_parsing_start_token_process(user_input, &index, ms);
	while (index < (int) ft_strlen(user_input) && temoin)
	{
		temoin = ft_parsing_cmd_process(user_input, &index, ms);
		if (temoin)
			temoin = ft_parsing_token_process(user_input, &index, ms);
	}
	temoin = ft_parse_cmd(ms->parse_s->c, ms);
	last = ft_go_to_last_cmd_node(ms->parse_s->c);
	if (last && last->tok_nxt_tok != end_input && ms->b_temoin)
	{
		ms->b_temoin = false;
		ft_print_invalid_end_token(ms, last->next_tok);
		//ft_print_invalid_token(ms, last->next_tok);
	}
}

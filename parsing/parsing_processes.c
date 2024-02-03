/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:07:28 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 17:14:51 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_parsing_cmd_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp;
	t_node	*buff;

	tmp = get_cmd(user_input, *from);
	if (!tmp)
		return (ft_print_msg("get_cmd issue", 'm', false, ms));
	buff = ft_create_cmd_node(tmp);
	if (!buff)
		return (free(tmp), ft_print_msg("node gen issue", 'm', false, ms));
	if (ms->parse_s->c == NULL)
	{
		ms->parse_s->c = buff;
		buff->prev_tok = ft_strdup(ms->tmp_str);
		if (!buff->prev_tok)
			return (free(buff), free(tmp), ft_set_val_ret(ms, false));
		buff->tok_prv_tok = ft_which_redir_token(buff->prev_tok, 'p');
		buff->b_is_file = ft_prev_is_red_io(buff);
	}
	else
		ft_add_node_to_cmds(ms, &ms->parse_s->c, buff);
	if (tmp)
		(*from) += (int) ft_strlen(tmp);
	free(tmp);
	return (true);
}

static bool	ft_parsing_start_embed(t_data *ms, char **tmp_t)
{
	if (!*tmp_t)
		return (false);
	if (!ft_is_valid_entry_token(*tmp_t))
	{
		ms->b_temoin = false;
		ft_print_invalid_start_token(ms, *tmp_t);
		free(*tmp_t);
		return (false);
	}
	return (true);
}

bool	ft_parsing_start_token_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp_t;

	while (ft_iswhitespace(user_input[*from]))
		(*from)++;
	tmp_t = get_token(user_input, *from);
	if (!ft_parsing_start_embed(ms, &tmp_t))
		return (false);
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

void	ft_parse_last_token(t_data *ms)
{
	t_node	*last;

	last = ft_go_to_last_cmd_node(ms->parse_s->c);
	if (last && last->tok_nxt_tok != end_input && ms->b_temoin)
	{
		ms->b_temoin = false;
		ft_print_invalid_end_token(ms, last->next_tok);
	}
}

void	ft_raw_parsing_process(char *user_input, t_data *ms)
{
	int		index;
	bool	temoin;
	t_node	*c;

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
	ft_parse_last_token(ms);
}

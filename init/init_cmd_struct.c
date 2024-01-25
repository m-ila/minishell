/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:08:23 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_empty_cmd(t_cmd *c, t_data *ms)
{
	if (c->tok_next_token == error)
	{
		ft_msg("ft_empty_cmd err", 'm', false, ms);
		return (false);
	}
	else if (c->tok_next_token == pipe_)
	{
		ft_msg(c->next_token, 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	else if (c->tok_next_token != pipe_ && \
	c->tok_next_token != end_of_file)
	{
		ft_msg("newline", 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	return (true);
}

static bool	ft_do(int d, t_cmd *c, t_data *ms)
{
	if (d == 1)
	{
		ft_msg(c->next_token, 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	if (d == 2)
	{
		ft_msg("failed gen ms->cmd", 'm', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	return (false);
}

bool	ft_set_val_ret(t_data *ms, bool ret)
{
	ms->b_temoin = false;
	return (ret);
}

/*
to do : free the precedent if wrong ?
or just turn temoin to false, so it would free at the end of the loop
if first elem of ep_all_elem is null, means c is only sep, so change val glob
val glob would be equal to 2 and print either a syntax err or return nothing
*/
bool	ft_parse_cmd(t_cmd *c, t_data *ms)
{
	if (!c)
		return (false);
	while (c && ms->b_temoin)
	{
		c->ep_model = ft_ep_model(c->raw_str, ft_cond_cut);
		c->all_elem = ft_ep_split(c->raw_str, c->ep_model, '0');
		if (!ft_var_env(ms, ms->parse_struct->struct_cmds))
			return (ft_set_val_ret(ms, false));
		free(c->ep_model);
		c->ep_model = ft_ep_model(c->raw_str, ft_cond_cut);
		c->ep_str = ft_ep_str(c->raw_str, c->ep_model);
		c->ep_all_elem = ft_ep_split(c->raw_str, c->ep_model, '0');
		if (ft_only_sep_base(c->ep_model, "0Ss"))
			return (ft_empty_cmd(c, ms));
		if (!c->ep_all_elem)
			return (false);
		if (!c->ep_all_elem[0])
			return (ft_do(1, c, ms));
		c->cmd = ft_strdup(c->ep_all_elem[0]);
		if (!c->cmd)
			return (ft_do(2, c, ms));
		c = c->next;
	}
	return (true);
}

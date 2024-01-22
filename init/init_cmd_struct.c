/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 19:44:09 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_empty_cmd(t_cmd *cmds, t_data *ms)
{
	if (cmds->tok_next_token == error)
	{
		ft_msg("ft_empty_cmd err", 'm', false, ms);
		return (false);
	}
	else if (cmds->tok_next_token == pipe_)
	{
		ft_msg(cmds->next_token, 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	else if (cmds->tok_next_token != pipe_ && \
	cmds->tok_next_token != end_of_file)
	{
		ft_msg("newline", 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	return (true);
}

static bool	ft_do(int d, t_cmd *cmds, t_data *ms)
{
	if (d == 1)
	{
		ft_msg(cmds->next_token, 's', false, ms);
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
if first elem of ep_cmd_w_arg is null, means cmds is only sep, so change val glob
val glob would be equal to 2 and print either a syntax err or return nothing
*/
bool	ft_parse_cmd(t_cmd *cmds, t_data *ms)
{
	if (!cmds)
		return (false);
	while (cmds && ms->b_temoin)
	{
		cmds->ep_model = ft_ep_model(cmds->raw_str, ft_cond_cut);
		cmds->cmd_w_arg = ft_split_epured(cmds->raw_str, cmds->ep_model, '0');
		if (!ft_var_env(ms, ms->parse_struct->struct_cmds))
			return (ft_set_val_ret(ms, false));
		free(cmds->ep_model);
		cmds->ep_model = ft_ep_model(cmds->raw_str, ft_cond_cut);
		cmds->epured_str = ft_epured_str(cmds->raw_str, cmds->ep_model);
		cmds->ep_cmd_w_arg = \
		ft_split_epured(cmds->raw_str, cmds->ep_model, '0');
		if (ft_only_sep_base(cmds->ep_model, "0Ss"))
			return (ft_empty_cmd(cmds, ms));
		if (!cmds->ep_cmd_w_arg)
			return (false);
		if (!cmds->ep_cmd_w_arg[0])
			return (ft_do(1, cmds, ms));
		cmds->cmd = ft_strdup(cmds->ep_cmd_w_arg[0]);
		if (!cmds->cmd)
			return (ft_do(2, cmds, ms));
		cmds = cmds->next;
	}
	return (true);
}

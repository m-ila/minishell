/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/15 20:49:14 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Not using the ft_split_fun anymore for this one
bool	ft_cut_here(char *str, char *model, int i)
{
	if (!str || !model || i >= (int) ft_strlen(model) || i >= (int) ft_strlen(str))
		return (false);
	if (model[i] == '0')
		return (true);
	return (false);
}
*/

bool	ft_empty_cmd(t_cmd *cmds, t_data *ms)
{
	if (cmds->tok_next_token == error)
	{
		ft_msg("ft_empty_cmd err", 'm', false, ms);
		return (false);
	}
	if (cmds->tok_next_token == end_of_file)
	{
		ft_msg("newline", 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	else if (cmds->tok_next_token != end_of_file)
	{
		ft_msg(cmds->next_token, 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	return (true);
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
		cmds->epured_model = ft_epured_model(cmds->raw_str);
		cmds->cmd_w_arg = ft_split_epured(cmds->raw_str, cmds->epured_model, '0');
		if (!ft_var_env(ms, ms->parse_struct->struct_cmds))
		{
			ms->b_temoin = false;
			return (false);
		}
		cmds->epured_str = ft_epured_str(cmds->raw_str, cmds->epured_model);
		cmds->ep_cmd_w_arg = \
		ft_split_epured(cmds->raw_str, cmds->epured_model, '0');
		if (ft_str_only_sep(cmds->epured_model, '0'))
			return (ft_empty_cmd(cmds, ms));
		if (!cmds->ep_cmd_w_arg)
			return (false);
		if (!cmds->ep_cmd_w_arg[0])
		{
			ft_msg(cmds->next_token, 's', false, ms);
			ms->b_temoin = false;
			return (false);
		}
		cmds->cmd = ft_strdup(cmds->ep_cmd_w_arg[0]);
		if (!cmds->cmd)
		{
			ft_msg("failed gen ms->cmd", 'm', false, ms);
			ms->b_temoin = false;
			return (false);
		}
		cmds = cmds->next;
	}
	return (true);
}

void	ft_cmd_display(t_cmd *cmds)
{
	int	i;

	i = 0;
	ft_printf_fd(1, "%s\n\n", PRINT_SEP_C);
	while (cmds)
	{
		ft_printf_fd(1, "cmd[%d]->raw_cmd = (d)%s(f)\n", i, cmds->raw_str);
		if (cmds->prev_token)
			ft_printf_fd(1, "prev token : (d)%s(f)\n", cmds->prev_token);
		if (cmds->next_token)
			ft_printf_fd(1, "next token : (d)%s(f)\n", cmds->next_token);
		if (cmds->cmd)
			ft_printf_fd(1, "cmd : (d)%s(f)\n", cmds->cmd);
		if (cmds->epured_model)
			ft_printf_fd(1, "epured_model : (d)%s(f)\n", cmds->epured_model);
		if (cmds->epured_str)
			ft_printf_fd(1, "epured_str : (d)%s(f)\n", cmds->epured_str);
		i++;
		cmds = cmds->next;
	}
}

/* to do : add ft_strdup protection */
void	ft_add_node_to_cmds(t_cmd **cmds, t_cmd *to_add)
{
	t_cmd	*end;

	if (!to_add)
		return ;
	if (!cmds)
	{
		*cmds = to_add;
		to_add->prev = NULL;
		return ;
	}
	end = ft_go_to_last_cmd_node(*cmds);
	end->next = to_add;
	to_add->prev = end;
	to_add->prev_token = ft_strdup(to_add->prev->next_token);
}

/* TO DO : change val globale */
t_cmd	*ft_create_cmd_node(char *raw_cmd)
{
	t_cmd	*new;

	if (!raw_cmd)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	if (*raw_cmd)
		new->raw_str = ft_strdup(raw_cmd);
	else
		new->raw_str = ft_strdup("");
	if (!new->raw_str)
	{
		ft_printf_fd(2, "fail to malloc for cmd : %s\n", raw_cmd);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev_token = NULL;
	new->next_token = NULL;
	new->epured_model = NULL;
	new->epured_str = NULL;
	new->ep_cmd_w_arg = NULL;
	new->cmd_w_arg = NULL;
	new->cmd = NULL;
	new->tok_next_token = end_of_file;
	new->tok_prev_token = error;
	return (new);
}

t_cmd	*ft_go_to_last_cmd_node(t_cmd *cmd_node)
{
	while (cmd_node)
	{
		if (!cmd_node->next)
			return (cmd_node);
		cmd_node = cmd_node->next;
	}
	return (NULL);
}

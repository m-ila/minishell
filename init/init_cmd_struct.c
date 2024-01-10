/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/10 12:32:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
to do : free the precedent if wrong ?
or just turn temoin to false, so it would free at the end of the loop
if first elem of cmd_w_arg is null, means cmds is only sep, so change val glob
val glob would be equal to 2 and print either a syntax err or return nothing
*/
bool	ft_parse_cmd(t_cmd *cmds, t_data *ms)
{
	if (!cmds)
		return (false);
	while (cmds)
	{
		cmds->cmd_w_arg = ft_split(cmds->raw_str, ' ');
		if (!cmds->cmd_w_arg)
			return (false);
		if (!cmds->cmd_w_arg[0])
		{
			ft_msg_end(cmds->next_token, 's', false, ms);
			ms->b_temoin = false;
			return (false);
		}
		cmds->cmd = ft_strdup(cmds->cmd_w_arg[0]);
		if (!cmds->cmd)
		{
			ft_msg_end("failed gen ms->cmd", 'm', false, ms);
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
		ft_printf_fd(1, "cmd[%d]->raw_cmd = '%s'\n", i, cmds->raw_str);
		if (cmds->prev_token)
			ft_printf_fd(1, "prev token : %s\n", cmds->prev_token);
		if (cmds->next_token)
			ft_printf_fd(1, "next token : %s\n", cmds->next_token);
		if (cmds->cmd)
			ft_printf_fd(1, "cmd : %s\n", cmds->cmd);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/04 11:34:32 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		i++;
		cmds = cmds->next;
	}
}

/* TO DO : if error, change glob val
bool	ft_cmd_struct(t_data *ms, char *user_input)
{
	t_cmd	*cmd_struct;
	t_cmd	*buff;
	int		i;

	if (!user_input)
		return (false);
	cmd_struct = NULL;
	if (!ms->arr_input)
		return (false);
	i = 0;
	while (ms->arr_input[i])
	{
		buff = ft_create_cmd_node(ms->arr_input[i]);
		if (!cmd_struct)
			cmd_struct = buff;
		else
			ft_add_node_to_cmds(&cmd_struct, buff);
		i++;
	}
	ms->parse_struct->struct_cmds = cmd_struct;
	return (true);
}
*/

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

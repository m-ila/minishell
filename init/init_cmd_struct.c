/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/30 21:18:02 by mbruyant         ###   ########.fr       */
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
		ft_printf_fd(1, "cmd[%d]->raw_cmd = %s\n", i, cmds->raw_str);
		i++;
		cmds = cmds->next;
	}
	ft_printf_fd(1, "%s\n\n", PRINT_SEP);
}

/* needs to make a function to free and to display */
bool	ft_cmd_struct(t_data *ms, char *user_input)
{
	t_cmd	*cmd_struct;
	t_cmd	*buff;
	char	**cmd_subarr;
	int		i;

	if (!user_input)
		return (false);
	cmd_struct = NULL;
	cmd_subarr = ft_split_base(user_input, BASE_TOKEN);
	if (!cmd_subarr)
		return (false);
	i = 0;
	while (cmd_subarr[i])
	{
		buff = ft_create_cmd_node(cmd_subarr[i]);
		if (!cmd_struct)
			cmd_struct = buff;
		else
			ft_add_node_to_cmds(&cmd_struct, buff);
		i++;
	}
	ft_free_2d_array(cmd_subarr);
	ms->parse_struct->struct_cmds = cmd_struct;
	return (true);
}

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
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:53:20 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:06:31 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	ft_set_char_to_null(&new->prev_token, &new->next_token, &new->ep_model);
	ft_set_char_to_null(&new->ep_str, &new->cmd, NULL);
	new->ep_all_elem = NULL;
	new->all_elem = NULL;
	new->tok_next_token = end_of_file;
	new->tok_prev_token = start;
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

/* to do : add ft_strdup protection */
void	ft_add_node_to_cmds(t_cmd **c, t_cmd *to_add)
{
	t_cmd	*end;

	if (!to_add)
		return ;
	if (!c)
	{
		*c = to_add;
		to_add->prev = NULL;
		return ;
	}
	end = ft_go_to_last_cmd_node(*c);
	end->next = to_add;
	to_add->prev = end;
	to_add->prev_token = ft_strdup(to_add->prev->next_token);
	to_add->tok_prev_token = ft_which_redir_token(to_add->prev_token, 'p');
}

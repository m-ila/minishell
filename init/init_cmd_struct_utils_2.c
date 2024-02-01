/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:26:50 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/01 14:30:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_go_to_last_cmd_node(t_node *cmd_node)
{
	while (cmd_node)
	{
		if (!cmd_node->next)
			return (cmd_node);
		cmd_node = cmd_node->next;
	}
	return (NULL);
}

t_node	*ft_create_cmd_node(char *raw_cmd)
{
	t_node	*new;

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
	ft_set_node_values(new);
	return (new);
}

void	ft_set_node_values(t_node *new)
{
	new->next = NULL;
	ft_set_char_to_null(&new->prev_tok, &new->next_tok, &new->ep_model);
	ft_set_char_to_null(&new->ep_str, &new->cmd, NULL);
	new->ep_all_elem = NULL;
	new->all_elem = NULL;
	new->cmd_w_args = NULL;
	new->b_is_file = false;
	new->tok_nxt_tok = end_input;
	new->tok_prv_tok = start;
}

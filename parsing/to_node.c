/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:45:43 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/23 13:48:18 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_prev_is_red_io(t_cmd *c)
{
	return (c->tok_prev_token == redir_in || \
	c->tok_prev_token == redir_out || \
	c->tok_prev_token == redir_out_app || \
	c->tok_prev_token == heredoc);
}

/* if not, starts by stdin */
/*
bool	ft_add_first_prev_token_node(char *str, t_cmd *c)
{
	if (!c)
		return (false);
	if (!str)
		return (true);
	c->prev_token = ft_strdup(str);
	c->tok_prev_token = ft_which_redir_token(c->prev_token, 'p');
	c->b_is_file = ft_prev_is_red_io(c);
	free(str);
	str = NULL;
	return (true);
}
*/
bool	ft_add_next_token_to_node(char *str, t_cmd *struct_cmd)
{
	t_cmd	*last;

	if (!struct_cmd || !str)
		return (false);
	last = ft_go_to_last_cmd_node(struct_cmd);
	last->next_token = ft_strdup(str);
	last->tok_next_token = ft_which_redir_token(last->next_token, 'n');
	return (true);
}

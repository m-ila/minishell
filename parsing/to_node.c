/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:45:43 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/18 16:18:17 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_add_prev_token_to_node(t_cmd *struct_cmd, t_data *ms)
{
	t_cmd	*tmp;
	printf("debug\n\n\n\n");

	if (!struct_cmd || !ms)
		return (false);
	if (!struct_cmd->next)
	{
		if (ms->tmp_str != NULL)
			struct_cmd->prev_token = ms->tmp_str;
		return (true);
	}
	if (!ft_add_first_prev_token_node(ms->tmp_str, struct_cmd))
		return (false);
	tmp = struct_cmd->next;
	while (tmp)
	{
		tmp->prev_token = tmp->prev->next_token;
		tmp->tok_prev_token = ft_which_redir_token(tmp->prev_token, 'p');
		tmp = tmp->next;
	}
	return (true);
}

/* if not, starts by stdin */
bool	ft_add_first_prev_token_node(char *str, t_cmd *c)
{
	if (!c)
		return (false);
	if (!str)
		return (true);
	c->prev_token = ft_strdup(str);
	c->tok_prev_token = ft_which_redir_token(c->prev_token, 'p');
	free(str);
	str = NULL;
	return (true);
}

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

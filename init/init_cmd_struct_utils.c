/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:53:20 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 07:54:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_assign_cmd_do(t_node *c)
{
	c->cmd = ft_strdup(c->ep_all_elem[0]);
	c->cmd_w_args = ft_copy_2d_array(c->ep_all_elem, 0, \
	ft_2d_lines(c->ep_all_elem));
	if (!c->cmd || !c->cmd_w_args)
	{
		ft_msg("malloc cmd & cmd_w_arg", 'm', false, NULL);
		return (ft_free_ret_2(&c->cmd, NULL, &c->cmd_w_args, false));
	}
	return (true);
}

bool	ft_assign_cmd(t_node *c)
{
	if (c->b_is_file)
	{
		c->cmd = NULL;
		if (ft_2d_lines(c->ep_all_elem) > 1)
		{
			c->cmd = ft_strdup(c->ep_all_elem[1]);
			c->cmd_w_args = ft_copy_2d_array(c->ep_all_elem, 1, \
			ft_2d_lines(c->ep_all_elem));
			if (!c->cmd || !c->cmd_w_args)
			{
				ft_msg("malloc cmd & cmd_w_arg", 'm', false, NULL);
				return (ft_free_ret_2(&c->cmd, NULL, &c->cmd_w_args, false));
			}
		}
	}
	if (!c->b_is_file && c->ep_all_elem)
		if (!ft_assign_cmd_do(c))
			return (false);
	return (true);
}

bool	ft_replace_str(char **str, char *n_str)
{
	if (!n_str || !str)
		return (false);
	ft_multiple_free(str, NULL, NULL);
	*str = ft_strdup(n_str);
	if (!*str)
		return (ft_print_msg("malloc error replace str", 'm', false, NULL));
	return (true);
}

/*
to do : add ft_strdup protection
*/
void	ft_add_node_to_cmds(t_node **c, t_node *to_add)
{
	t_node	*end;

	if (!to_add)
		return ;
	end = ft_go_to_last_cmd_node(*c);
	if (!end)
		return ;
	end->next = to_add;
	to_add->prev = end;
	to_add->prev_tok = ft_strdup(to_add->prev->next_tok);
	to_add->tok_prv_tok = ft_which_redir_token(to_add->prev_tok, 'p');
	to_add->b_is_file = ft_prev_is_red_io(to_add);
}

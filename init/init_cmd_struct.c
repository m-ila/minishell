/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 11:06:54 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_consecutive_empty_node(t_node *c, t_data *ms)
{
	if (ft_only_sep_base(c->ep_model, "0Ss") && c->tok_nxt_tok == pipe_)
	{
		ft_msg(c->next_tok, 's', false, ms);
		return (ft_set_val_ret(ms, true));
	}
	if (ft_only_sep_base(c->ep_model, "0Ss") && \
	ft_redir_io_token(c->tok_nxt_tok) && \
	ft_redir_io_token(c->tok_prv_tok))
	{
		ft_msg(c->next_tok, 's', false, ms);
		return (ft_set_val_ret(ms, true));
	}
	if (c->next && ft_only_sep_base(c->ep_model, "0Ss") && \
	ft_only_sep_base(c->next->ep_model, "0Ss"))
	{
		ft_msg(c->next_tok, 's', false, ms);
		return (ft_set_val_ret(ms, true));
	}
	if (!c->next && ft_only_sep_base(c->ep_model, "0Ss"))
	{
		ft_msg("newline", 's', false, ms);
		return (ft_set_val_ret(ms, true));
	}
	if (ft_is_io_redirect(ms->parse_s->c->tok_prv_tok) && \
	ms->parse_s->c->tok_nxt_tok == end_input \
	&& ft_only_sep_base(c->ep_model, "0Ss"))
	{
		ft_msg(ms->parse_s->c->next_tok, 's', false, ms);
		return (false);
	}
	return (false);
}

/*
Only triggered when a node is empty, therefore no file or cmd
*/
bool	ft_valid_consecutive_redir_tok(t_node *c, t_data *ms)
{
	printf("ft_valid_consecutive_redir_tok entry\n");
	if (c->next && c->tok_nxt_tok == pipe_)
	{
		printf("ft_valid_consecutive_redir_tok entry 2\n");
		if (c->next->tok_nxt_tok == pipe_)
		{
			ft_msg(c->next_tok, 's', false, ms);
			return (ft_set_val_ret(ms, false));
		}
	}
	printf("ft_valid_consecutive_redir_tok returns true\n");
	return (true);
}

static bool	ft_do(int d, t_node *c, t_data *ms)
{
	if (d == 1)
	{
		ft_msg(c->next_tok, 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	if (d == 2)
	{
		ms->b_temoin = false;
		return (false);
	}
	return (false);
}

/* 
si pas vide, s'arrête directement
si vide, checke si le node d'après l'est aussi
si vide et le suivant non, checke validité des tokens ( |< valide etc)
*/
bool	ft_deal_w_empty_elems(t_node *c, t_data *ms)
{
	printf("ft_deal_w_empty_elem entry\n");
	if (!ft_only_sep_base(c->ep_model, "0Ss"))
		return (true);
	if (!ft_valid_consecutive_redir_tok(c, ms))
		return (false);
	if (ft_consecutive_empty_node(c, ms))
		return (false);
	if (ft_only_sep_base(c->ep_model, "0Ss") && c->tok_nxt_tok == pipe_)
		return (false);
	return (true);
}

/*
to do : free the precedent if wrong ?
or just turn temoin to falsenewline, so it would free at the end of the loop
if first elem of ep_all_elem is null, means c is only sep, so change val glob
val glob would be equal to 2 and print either a syntax err or return nothing
*/
bool	ft_parse_cmd(t_node *c, t_data *ms)
{
	if (!c)
		return (false);
	while (c && ms->b_temoin)
	{
		if (!ft_epuring_process(ms, c))
			return (false);
		if (!ft_deal_w_empty_elems(c, ms))
			return (false);
		if (!c->ep_all_elem)
			return (false);
		if (!c->ep_all_elem[0])
			return (ft_do(1, c, ms));
		if (!ft_assign_cmd(c))
			return (ft_do(2, c, ms));
		c = c->next;
	}
	return (true);
}

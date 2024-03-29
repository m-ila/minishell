/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 16:54:43 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_sub_cond(t_node *c, t_data *ms)
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
	return (false);
}

bool	ft_consecutive_empty_node(t_node *c, t_data *ms)
{
	if (ft_sub_cond(c, ms))
		return (true);
	if (!c->next && ft_only_sep_base(c->ep_model, "0Ss") && c->prev)
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

bool	ft_parse_cmd(t_node *c, t_data *ms)
{
	if (!c)
		return (false);
	while (c && ms->b_temoin)
	{
		if (!ft_epuring_process(ms, c))
			return (ft_set_val_ret(ms, false));
		if (!ft_deal_w_empty_elems(c, ms))
			return (ft_set_val_ret(ms, false));
		if (!c->ep_all_elem)
			return (ft_set_val_ret(ms, false));
		if (!c->ep_all_elem[0])
			return (ft_do(1, c, ms));
		if (!ft_assign_cmd(c))
			return (ft_do(2, c, ms));
		c = c->next;
	}
	return (true);
}

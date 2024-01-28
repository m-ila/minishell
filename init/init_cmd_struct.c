/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 16:36:13 by mbruyant         ###   ########.fr       */
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
	return (false);
}

/*
Only triggered when a node is empty, therefore no file or cmd
*/
bool	ft_valid_consecutive_redir_tok(t_node *c, t_data *ms)
{
	if (c->next && c->tok_nxt_tok == pipe_)
	{	
		if (c->next->tok_nxt_tok == pipe_)
		{
			ft_msg(c->next_tok, 's', false, ms);
			return (ft_set_val_ret(ms, false));
		}
	}
	return (true);
}

/*
bool	ft_empty_cmd(t_node *c, t_data *ms)
{
	if (c->tok_nxt_tok == error)
	{
		ft_msg("ft_empty_cmd err", 'm', false, ms);
		return (false);
	}
	else if (c->tok_nxt_tok == pipe_)
	{
		ft_msg(c->next_tok, 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	else if (c->tok_nxt_tok != pipe_ && \
	c->tok_nxt_tok != end_input)
	{
		ft_msg("newline", 's', false, ms);
		ms->b_temoin = false;
		return (false);
	}
	return (true);
}
*/

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
		//ft_msg("failed gen ms->cmd", 'm', false, ms);
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
	return (true);
}

bool	ft_refresh_ep_model(t_node *c)
{
	char	*refreshed;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(c->ep_model) - ft_strocc(c->ep_model, '0');
	refreshed = ft_calloc(len + 1, sizeof(char));
	if (!refreshed)
		return (false);
	while (i < len)
	{
		if (c->ep_model[i] != '0')
		{
			refreshed[j] = c->ep_model[i];
			j++;
		}
		i++;
	}
	printf("REFRESHED MODEL : %s\n", refreshed);
	free(c->ep_model);
	c->ep_model = refreshed;
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
		c->ep_model = ft_ep_model(c->raw_str, ft_cond_cut);
		c->all_elem = ft_split_epured(c->raw_str, c->ep_model, '0');
		if (!ft_var_env(ms, ms->parse_s->c))
			return (ft_set_val_ret(ms, false));
		c->ep_str = ft_ep_str(c->raw_str, c->ep_model);
//		ft_refresh_ep_model(c);
		c->ep_all_elem = ft_split_epured(c->raw_str, c->ep_model, '0');
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

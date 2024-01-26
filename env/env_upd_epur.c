/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_upd_epur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:54:09 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 17:12:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_epur_str2(t_data *ms, char **str2, char **str1)
{
	if (ms->parse_s->tmp_val)
		*str2 = ft_ep_model(ms->parse_s->tmp_val, ft_cond_cut);
	if (!ms->parse_s->tmp_val)
		*str2 = ft_strdup("");
	if (!str2)
	{
		free(*str1);
		ms->b_temoin = false;
		return (false);
	}
	return (true);
}

static bool	ft_nest_update_epur(t_data *ms, t_parse *p, t_node *c, int *i)
{
	if (*i == 0)
		p->str1 = ft_strdup("");
	else
		p->str1 = ft_strdup_limiters(c->ep_model, 0, *i);
	if (!p->str1)
	{
		ms->b_temoin = false;
		return (ft_print_msg("up epur str1", 'm', false, ms));
	}
	if (!ft_epur_str2(ms, &p->str2, &p->str1))
		return (ft_print_msg("up epur str2", 'm', false, ms));
	p->str3 = ft_strdup_limiters(c->ep_model, \
	*i + ft_strlen(ms->parse_s->tmp_tag) + 1, \
	ft_strlen(c->ep_model));
	if (!p->str3)
	{
		ft_multiple_free(&p->str1, &p->str2, NULL);
		ms->b_temoin = false;
		return (ft_print_msg("up epur str3", 'm', false, ms));
	}
	return (true);
}

bool	ft_update_epur(t_data *ms, t_node *c, int *i)
{
	t_parse	*p;

	p = ms->parse_s;
	if (!ft_nest_update_epur(ms, p, c, i))
		return (false);
	free(c->ep_model);
	c->ep_model = ft_triple_join(p->str1, p->str2, p->str3, ms);
	ft_multiple_free(&p->str1, &p->str2, &p->str3);
	if (!c->ep_model)
	{
		ms->b_temoin = false;
		return (ft_print_msg("update epured model", 'm', false, ms));
	}
	return (true);
}

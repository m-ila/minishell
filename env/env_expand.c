/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:31:38 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/01 16:18:45 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_nest_join_values(t_data *ms, t_parse *p, t_node *c, int *i)
{
	if (*i == 0)
		p->str1 = ft_strdup("");
	else
		p->str1 = ft_strdup_limiters(c->raw_str, 0, *i);
	if (!p->str1)
	{
		ms->b_temoin = false;
		return (ft_print_msg("join val str1", 'm', false, ms));
	}
	p->str3 = ft_strdup_limiters(c->raw_str, \
	*i + ft_strlen(ms->parse_s->tmp_tag) + 1, ft_strlen(c->raw_str));
	if (!p->str3)
	{
		free(p->str1);
		ms->b_temoin = false;
		return (ft_print_msg("join val str3", 'm', false, ms));
	}
	return (true);
}

bool	ft_join_values(t_data *ms, t_node *c, int *i)
{
	t_parse	*p;

	p = ms->parse_s;
	if (!ft_nest_join_values(ms, p, c, i))
		return (false);
	free(c->raw_str);
	c->raw_str = ft_triple_join(p->str1, ms->parse_s->tmp_val, \
	p->str3, ms);
	ft_multiple_free(&p->str1, NULL, &p->str3);
	if (!c->raw_str)
	{
		ms->b_temoin = false;
		return (ft_print_msg("join val raw str", 'm', false, ms));
	}
	return (true);
}

bool	ft_do_in_env(t_data *ms, t_node *c, t_parse *ps, int *i)
{
	if (ft_tag_is_in_env(ms, ps->tmp_tag))
	{
		if (!ft_strncmp(ps->tmp_tag, "?", ft_strlen(ps->tmp_tag)))
			ft_comp_var_env(ms);
		ps->tmp_val = ft_get_val_in_env(ms->envi, ps->tmp_tag, ms);
	}
	if (!ft_tag_is_in_env(ms, ps->tmp_tag))
		ps->tmp_val = ft_strdup("");
	if (!ps->tmp_val)
		return (ft_print_msg("strdup env val", 'm', false, ms));
	if (!ft_join_values(ms, c, i))
		return (false);
	if (!ft_update_epur(ms, c, i))
		return (false);
	(*i) = (*i) + ft_strlen(ps->tmp_val) - 1;
	free(ps->tmp_val);
	return (true);
}

bool	ft_var_env(t_data *ms, t_node *c)
{
	int		i;
	t_parse	*ps;

	if (!ms->b_temoin || !c->ep_model || !c->raw_str)
		return (false);
	if (!ft_strocc(c->ep_model, '$'))
		return (true);
	i = 0;
	ps = ms->parse_s;
	while (i < (int) ft_strlen(c->raw_str))
	{
		ft_set_char_to_null(&ps->tmp_tag, &ps->tmp_val, NULL);
		if (c->ep_model[i] == '$')
		{
			ps->tmp_tag = ft_get_val_to_search_in_env(ms, c, i + 1);
			if (!ps->tmp_tag)
				return (ft_print_msg("strdup env tag", 'm', false, ms));
			if (!ft_do_in_env(ms, c, ps, &i))
				return (false);
			free(ps->tmp_tag);
		}
		i++;
	}
	return (true);
}

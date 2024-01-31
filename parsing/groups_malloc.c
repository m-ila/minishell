/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:59:38 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/31 18:52:20 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_grp_node(t_group **og, t_group *to_add)
{
	t_group	*last;

	if (!to_add)
		return ;
	if (!og || !(*og))
	{
		*og = to_add;
		return ;
	}
	last = ft_go_to_last_group_node(*og);
	last->next = to_add;
	to_add->prev = last;
	printf("group added\n\n");
}

static bool	ft_tmp_file(t_data *ms, t_group *grp)
{
	char	*result;
	char	*tmp;

	tmp = ft_itoa(grp->gr_id);
	if (!tmp)
		return (false);
	result = ft_triple_join(".", tmp, ".tmp", ms);
	if (!result)
		return (ft_free_return(&tmp, NULL, NULL, false));
	grp->gr_id_str = result;
	return (ft_free_return(&tmp, NULL, NULL, true));
}

void	ft_malloc_group_struct(t_data *ms, t_parse *p)
{
	t_group	*buff;
	int		i;

	i = 0;
	printf("gr_nb : %ld\n", p->gr_nb);
	while ((size_t) i < p->gr_nb)
	{
		buff = ft_init_group_node();
		buff->gr_id = i;
		if (!ft_tmp_file(ms, buff) || !buff->gr_id_str)
		{
			free(buff);
			ft_free_groups(ms, &p->gr);
			ft_set_r_val(R_ERR_GEN, ms);
			ms->b_temoin = false;
			return ;
		}
		if (!p->gr)
			p->gr = buff;
		else
			ft_add_grp_node(&p->gr, buff);
		i++;
	}
}

void	ft_init_group_struct(t_data *ms, t_parse *p)
{
	t_node	*from;
	t_node	*until;
	t_group	*groups;

	from = p->c;
	until = ft_get_delim_node(&from);
	printf("from node 1 elem : %s\n", until->ep_all_elem[0]);
	groups = p->gr;
	while (from && until && groups)
	{
		ft_fill_group_struct(ms, p, &from, groups);
		groups = groups->next;
		until = ft_get_delim_node(&from);
	}
}

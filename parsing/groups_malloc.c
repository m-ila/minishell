/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:59:38 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 22:03:54 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_grp_node(t_group **og, t_group *to_add)
{
	t_group	*last;

	if (!to_add)
		return ;
	if (!og)
	{
		*og = to_add;
		return ;
	}
	last = ft_go_to_last_group_node(*og);
	last->next = to_add;
	to_add->prev = last;
	printf("group added\n\n");
}

void	ft_malloc_group_struct(t_parse *p)
{
	t_group	*buff;
	size_t	i;

	i = 0;
	printf("gr_nb : %ld\n", p->gr_nb);
	while (i < p->gr_nb)
	{
		buff = ft_init_group_node();
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

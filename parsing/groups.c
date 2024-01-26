/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:14:18 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 21:39:55 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_groups(t_data *ms, t_parse *p)
{
	t_group	*navig;

	ft_get_nb_group(ms);
	ft_malloc_group_struct(p);
	ft_init_group_struct(ms, p);
	if (p->gr)
	{
		navig = p->gr;
		while (navig)
		{
			printf("group created\n");
			printf("infile : %ld\noutfile : %ld\n\n", navig->gr_nb_infile, navig->gr_nb_outfile);
			navig = navig->next;
		}
	}
	return (true);
}

void	ft_get_nb_group(t_data *ms)
{
	size_t	group_nb;
	t_node	*index;

	if (!ms || !ms->b_temoin || !ms->parse_s || !ms->parse_s->c)
		return ;
	group_nb = 0;
	index = ms->parse_s->c;
	while (index)
	{
		if (index->tok_nxt_tok == pipe_ || index->tok_nxt_tok == end_input)
			group_nb++;
		if (index->tok_nxt_tok == end_input)
			break;
		index = index->next;
	}
	ms->parse_s->gr_nb = group_nb;
}

t_group	*ft_init_group_node(void)
{
	t_group	*g;

	g = ft_calloc(1, sizeof(t_group));
	if (!g)
		return (NULL);
	g->prev = NULL;
	g->next = NULL;
	g->gr_fd_in = -1;
	g->gr_fd_out = -1;
	g->gr_nb_infile = 0;
	g->gr_nb_outfile = 0;
	g->node_arr = NULL;
	return (g);
}

void	ft_add_grp_node(t_group **og, t_group *to_add)
{
	if (!to_add)
		return ;
	if (!og)
	{
		*og = to_add;
		return ;
	}
	while ((*og)->next)
		(*og) = (*og)->next;
	(*og)->next = to_add;
	to_add->prev = (*og);
	printf("group added\n\n");
}

void	ft_malloc_group_struct(t_parse *p)
{
	t_group	*buff;
	size_t	i;

	i = 0;
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

t_node	*ft_get_delim_node(t_node **from)
{
	t_node	*delim;

	delim = *from;
	while (delim)
	{
		if (delim->tok_nxt_tok == pipe_ || delim->tok_nxt_tok == end_input)
			return (delim);
		delim = delim->next;
	}
	return (NULL);
}

/* il faut compter le limiteur aussi */
bool	ft_fill_group_struct(t_data *ms, t_parse *p, t_node **from, t_group *g)
{
	t_node	*until;
	int		i;

	if (!ms || !ms->b_temoin || !p || !from)
		return (false);
	until = ft_get_delim_node(from);
	i = 0;
	while (*from)
	{
		if (i > 0 && (*from)->prev == until)
			break;
		if ((*from)->tok_prv_tok == redir_in || (*from)->tok_prv_tok == heredoc)
			g->gr_nb_infile++;
		if ((*from)->tok_prv_tok == redir_out || (*from)->tok_prv_tok == redir_out_app)
			g->gr_nb_outfile++;
		(*from) = (*from)->next;
		i++;
	}
	return (true);
}

/*
size_t	ft_get_nb_node(t_data *ms, t_parse *p, t_node *from)
{
	t_node	*index;
	t_node	*until;
	size_t	nb_node;

	if (!ms || !ms->b_temoin || !p || !from)
		return (0);
	index = from;
	until = ft_get_delim_node(index);
	nb_node = 0;
	while (index)
	{
		if (index->prev == until)
			break;
		nb_node++;
		index = index->next;
	}
	return (nb_node);
}
*/

void	ft_free_groups(t_group **gr)
{
	t_group	*index;

	if (*gr == NULL)
		printf("GROUP EST NULL\n");
	while (*gr)
	{
		index = *gr;
		(*gr) = (*gr)->next;
		free(index);
		index = NULL;
		printf("free completed !\n");
	}
}

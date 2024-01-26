/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:14:18 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 23:17:14 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
bool	ft_malloc_arr(t_group *grp, char which)
{

}

bool	ft_malloc_io_arrs(t_data *ms, t_parse *p)
{
	t_group	*grp;
	size_t	i;

	if (!ms->b_temoin)
		return (true);
	grp = p->gr;
	while (i < p->gr_nb)
	{
		if ()
		i++;
	}
}
*/

bool	ft_groups(t_data *ms, t_parse *p)
{
	t_group	*navig;

	if (!ms->b_temoin)
		return (true);
	ft_get_nb_group(ms);
	ft_malloc_group_struct(p);
	ft_init_group_struct(ms, p);
	if (p->gr)
	{
		navig = p->gr;
		while (navig)
		{
			printf("group created\n");
			printf("infile : %ld\noutfile : %ld\n\n", \
			navig->gr_nb_infile, navig->gr_nb_outfile);
			navig = navig->next;
		}
	}
	return (true);
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

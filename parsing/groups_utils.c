/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:56:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 13:58:38 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_group	*ft_init_group_node(void)
{
	t_group	*g;

	g = ft_calloc(1, sizeof(t_group));
	if (!g)
	{
		ft_msg("malloc error init group", 'm', false, NULL);
		return (NULL);
	}
	g->prev = NULL;
	g->next = NULL;
	g->gr_fd_in = -1;
	g->gr_fd_out = -1;
	g->gr_nb_infile = 0;
	g->gr_nb_outfile = 0;
	g->gr_nb_elems = 0;
	g->cmd_and_args = NULL;
	g->outfile_arr = NULL;
	g->infile_arr = NULL;
	return (g);
}

t_group	*ft_go_to_last_group_node(t_group *gr)
{
	while (gr->next)
		gr = gr->next;
	return (gr);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:14:18 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 11:53:26 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_is_input_redirect(t_tokens t)
{
	return (t == heredoc || t == redir_in);
}

bool	ft_is_output_redirect(t_tokens t)
{
	return (t == redir_out || t == redir_out_app);
}

/*
bool	ft_malloc_t_out_arr(t_group *p)
{
	t_tokens	*type_t;
	if (!p)
		return (false);
	if (p->gr_nb_outfile == 0)
		return (true);
	p->t_outfile_arr = ft_calloc(p->gr_nb_outfile + 1, sizeof(type_t));
	if (!p->t_outfile_arr)
		return (false);
	return (true);
}
*/

bool	ft_fill_t_out_arr(t_data *ms, t_group *grp, t_node *from, t_node *until)
{
	size_t	i;
	t_node	*navig;
	char	*tmp;

	if (!ms->b_temoin || !grp->gr_nb_outfile)
		return (true);
	i = 0;
	navig = from;
	while (navig && i < grp->gr_nb_outfile)
	{
		if (i > 0 && navig->prev == until)
			break;
		if (ft_is_output_redirect(navig->tok_prv_tok))
		{
			tmp = ft_triple_join(navig->prev_tok, " ", navig->ep_all_elem[0], ms);
			if (!tmp || !ft_add_str_to_tab(&grp->outfile_arr, tmp))
				return (false);
			ft_multiple_free(&tmp, NULL, NULL);
			printf("node : %p\n", grp);
			i++;
		}
		navig = navig->next;
	}
	printf("element dans fill_out_arr : %ld\n", i);
	return (true);
}

/*
bool	ft_malloc_t_in_arr(t_group *p)
{
	t_tokens	*type_t;

	if (!p)
		return (false);
	if (p->gr_nb_infile == 0)
		return (true);
	p->t_infile_arr = ft_calloc(p->gr_nb_infile + 1, sizeof(*type_t));
	if (!p->t_infile_arr)
		return (false);
	printf("t_infile_arr created, size : %ld + 1 \n\n\n", p->gr_nb_infile);
	return (true);
}
*/
/*
to do : 
malloc protection and free
*/
bool	ft_fill_t_in_arr(t_data *ms, t_group *grp, t_node *from, t_node *until)
{
	size_t	i;
	t_node	*navig;
	char	*tmp;

	if (!ms->b_temoin || !grp->gr_nb_infile)
		return (true);
	i = 0;
	navig = from;
	while (navig && i < grp->gr_nb_infile)
	{
		if (i > 0 && navig->prev == until)
			break;
		if (ft_is_input_redirect(navig->tok_prv_tok))
		{
			tmp = ft_triple_join(navig->prev_tok, " ", navig->ep_all_elem[0], ms);
			if (!tmp || !ft_add_str_to_tab(&grp->infile_arr, tmp))
				return (false);
			ft_multiple_free(&tmp, NULL, NULL);
			printf("node : %p\n", grp);
			i++;
		}
		printf("(t_in_arr)next node\n");
		navig = navig->next;
	}
	return (true);
}

bool	ft_init_data_groups(t_data *ms, t_parse *p)
{
	t_node	*navig_node;
	t_node	*delim;
	t_group	*gp_navig;
	size_t	i;

	i = 0;
	navig_node = p->c;
	gp_navig = p->gr;
	while (navig_node && i < p->gr_nb)
	{
		delim = ft_get_delim_node(&navig_node);
		if (!ft_fill_t_in_arr(ms, gp_navig, navig_node, delim))
		{
			printf("error 2\n");
			break ;
		}
		if (!ft_fill_t_out_arr(ms, gp_navig, navig_node, delim))
		{
			printf("error 4\n");
			break ;
		}
		navig_node = delim->next;
		gp_navig = gp_navig->next;
	}
	return (true);
}

bool	ft_groups(t_data *ms, t_parse *p)
{
	if (!ms->b_temoin)
		return (true);
	ft_get_nb_group(ms);
	ft_malloc_group_struct(p);
	ft_init_group_struct(ms, p);
	ft_init_data_groups(ms, p);
	if (p->gr)
		ft_group_diplay(p);
	return (true);
}

/* il faut compter le limiteur aussi */
bool	ft_fill_group_struct(t_data *ms, t_parse *p, t_node **from, t_group *g)
{
	t_node	*until;
	int		i;

	if (!ms || !ms->b_temoin || !p)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:51:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 14:14:53 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_special_case(t_node *navig)
{
	return (navig->tok_prv_tok == pipe_ && \
	ft_is_io_redirect(navig->tok_nxt_tok) && \
	ft_only_sep_base(navig->ep_model, "0sS"));
}

/*
to do : secure the return false with a multiple free
*/
bool	ft_fill_out_arr(t_data *ms, t_group *grp, t_node *from, t_node *until)
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
			i++;
		}
		navig = navig->next;
	}
	return (true);
}

/*
to do : 
malloc protection and free
*/
bool	ft_fill_in_arr(t_data *ms, t_group *grp, t_node *from, t_node *until)
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
			i++;
		}
		navig = navig->next;
	}
	return (true);
}

bool	ft_fill_cmd_in_groups(t_data *ms, t_group *grp, t_node *from, t_node *until)
{
	size_t	i;
	t_node	*navig;

	if (!ms->b_temoin)
		return (true);
	i = 0;
	navig = from;
	while (navig)
	{
		if ((i > 0 && navig->prev == until) || i >= grp->gr_nb_elems)
			return (true);
		if (navig->cmd && i < grp->gr_nb_elems && !ft_special_case(navig))
			if (!ft_add_tabs(&grp->cmd_and_args, navig->cmd_w_args))
				return (false);
		navig = navig->next;
		i++;
	}
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
		g->gr_nb_elems++;
		(*from) = (*from)->next;
		i++;
	}
	return (true);
}

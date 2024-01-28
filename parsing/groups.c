/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:14:18 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 13:05:31 by mbruyant         ###   ########.fr       */
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
		if (navig->cmd && i < grp->gr_nb_elems)
			if (!ft_add_tabs(&grp->cmd_and_args, navig->cmd_w_args))
				return (false);
		navig = navig->next;
		i++;
	}
	return (true);
}

/*
to do : change the printf, break into ms->b_temoin false and ft_msg
*/
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
		if (!ft_fill_cmd_in_groups(ms, gp_navig, navig_node, delim))
		{
			printf("error 5\n");
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
		g->gr_nb_elems++;
		(*from) = (*from)->next;
		i++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:14:18 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/02 17:28:11 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (navig_node && i < p->gr_nb && g_return_val != -1)
	{
		delim = ft_get_delim_node(&navig_node);
		if (!ft_fill_in_arr(ms, gp_navig, navig_node, delim))
		{
			printf("error 2\n");
			break ;
		}
		if (!ft_fill_out_arr(ms, gp_navig, navig_node, delim))
		{
			printf("error 4\n");
			break ;
		}
		if (!ft_fill_cmd_in_groups(ms, gp_navig, navig_node, delim))
		{
			printf("error 5\n");
			break ;
		}
		ft_set_fd_grps(ms, p, gp_navig);
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
	ft_malloc_group_struct(ms, p);
	ft_init_group_struct(ms, p);
	ft_init_data_groups(ms, p);
//	if (p->gr)
		//ft_group_diplay(p);
	return (true);
}

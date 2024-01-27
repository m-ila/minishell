/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:43:16 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/27 02:30:57 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_group_diplay(t_parse *p)
{
	t_group	*group;
	int		i;
	int		j;
	int		id_nb;

	group = p->gr;
	id_nb = 1;
	while (group)
	{
		i = -1;
		j = -1;
		printf("group %d created%s\n", id_nb, PRINT_SEP);
		printf("infile : %ld\noutfile : %ld\n\n", \
		group->gr_nb_infile, group->gr_nb_outfile);
		if (group->infile_arr)
		{
			while (group->infile_arr[++i])
				printf("infile_arr[%d] : %s\n", i, group->infile_arr[i]);
		}
		if (group->t_infile_arr)
		{
			i = -1;
			while (group->t_infile_arr[++i])
				printf("t_infile_arr[%d] : %d\n", i, group->t_infile_arr[i]);
		}
		if (group->outfile_arr)
		{
			while (group->outfile_arr[++j])
				printf("outfile_arr[%d] : %s\n", j, group->outfile_arr[j]);
		}
		if (group->t_outfile_arr)
		{
			j = -1;
			while (group->t_outfile_arr[++j])
				printf("t_outfile_arr[%d] : %d\n\n", j, group->t_outfile_arr[j]);
		}
		id_nb++;
		group = group->next;
	}
}

void	ft_cmd_display(t_data *ms, t_node *c)
{
	int	i;
	int	j;

	i = 0;
	if (!ms->b_temoin)
		return ;
	ft_printf_fd(1, "%s\n\n", PRINT_SEP_C);
	while (c)
	{
		j = -1;
		ft_printf_fd(1, "cmd[%d]->raw_cmd = (d)%s(f)\n", i, c->raw_str);
		if (c->prev_tok)
			ft_printf_fd(1, "prev token : (d)%s(f)\n", c->prev_tok);
		if (c->next_tok)
			ft_printf_fd(1, "next token : (d)%s(f)\n", c->next_tok);
		if (c->cmd)
			ft_printf_fd(1, "cmd : (d)%s(f)\n\n", c->cmd);
		if (c->ep_model)
			ft_printf_fd(1, "ep_model : (d)%s(f)\n", c->ep_model);
		if (c->ep_str)
			ft_printf_fd(1, "ep_str : (d)%s(f)\n\n", c->ep_str);
		while (c->ep_all_elem[++j])
			ft_printf_fd(1, "ep_all_elem[%d] : (d)%s(f)\n", j, c->ep_all_elem[j]);
		j = -1;
		ft_printf_fd(1, "\n");
		if (c->cmd_w_args != NULL)
		{
			while (c->cmd_w_args[++j])
				ft_printf_fd(1, "cmd_w_arg[%d] : (d)%s(f)\n", j, c->cmd_w_args[j]);
		}
		printf("is file : %d\n", c->b_is_file);
		printf("\nprev tok : %d\n", c->tok_prv_tok);
		printf("next tok : %d\n\n\n", c->tok_nxt_tok);
		i++;
		c = c->next;
	}
}

void	print_values(t_data *ms)
{
	ft_printf_fd(1, "%s\n\n", PRINT_SEP_T);
	ft_printf_fd(1, "ms->user_input = %s\nms->printed_line = %s\n\n", \
	ms->user_input, ms->printed_line);
/*
	ft_printf_fd(1, "ms->curr_wd = %s\nms->prev_w_dir = %s\n\n", \
	ms->curr_work_dir, ms->prev_work_dir);
*/
	ft_printf_fd(1, "ms->b_temoin = %d\n", (int) ms->b_temoin);
	if (ms->parse_s->c)
		ft_cmd_display(ms, ms->parse_s->c);
	ft_printf_fd(1, "%s\n\n\n", PRINT_SEP);
}

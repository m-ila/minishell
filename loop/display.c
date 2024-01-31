/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:43:16 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/31 16:52:08 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_display_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		ft_printf_fd(1, "n°%d : (d)%s(f)\n", i, arr[i]);
	ft_printf_fd(1, "\n\n");
}

void	ft_display_interpreted_array(char **arr)
{
	int		i;
	char	*tmp;

	i = -1;
	while (arr[++i])
	{
		tmp = ft_get_file_name(arr[i]);
		ft_printf_fd(1, "n°%d : (d)%s(f)\n", i, arr[i]);
		printf("file name : (d)%s(f)\ntoken value : %d\n", tmp, \
		ft_get_token(arr[i]));
		ft_multiple_free(&tmp, NULL, NULL);
	}
	ft_printf_fd(1, "\n\n");
}

void	ft_group_diplay(t_parse *p)
{
	t_group	*group;

	group = p->gr;
	while (group)
	{
		printf("======== group %d ========\n", group->gr_id);
		printf("group node adress : %p\n", group);
		printf("group nb elem : %ld\n", group->gr_nb_elems);
		printf("group fdin : %d\ngroup fdout : %d\n", group->gr_fd_in, \
		group->gr_fd_out);
		printf("group id_str : %s\n", group->gr_id_str);
		if (group->gr_nb_infile)
		{
			ft_printf_fd(1, "infile_arr\n\n");
			ft_display_interpreted_array(group->infile_arr);
		}
		if (group->gr_nb_outfile)
		{
			ft_printf_fd(1, "outfile_arr\n\n");
			ft_display_interpreted_array(group->outfile_arr);
		}
		if (group->cmd_and_args)
		{
			ft_printf_fd(1, "cmd_and_args\n\n");
			ft_display_array(group->cmd_and_args);
		}
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

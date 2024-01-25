/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:43:16 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/25 16:57:39 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_display(t_data *ms, t_cmd *c)
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
		if (c->prev_token)
			ft_printf_fd(1, "prev token : (d)%s(f)\n", c->prev_token);
		if (c->next_token)
			ft_printf_fd(1, "next token : (d)%s(f)\n", c->next_token);
		if (c->cmd)
			ft_printf_fd(1, "cmd : (d)%s(f)\n", c->cmd);
		if (c->ep_model)
			ft_printf_fd(1, "ep_model : (d)%s(f)\n", c->ep_model);
		if (c->ep_str)
			ft_printf_fd(1, "ep_str : (d)%s(f)\n", c->ep_str);
		while (c->ep_all_elem[++j])
			ft_printf_fd(1, "\nep_all_elem[%d] : (d)%s(f)\n", j, c->ep_all_elem[j]);
		j = -1;
		if (c->cmd_w_args != NULL)
		{
			while (c->cmd_w_args[++j])
				ft_printf_fd(1, "\ncmd_w_arg[%d] : (d)%s(f)\n", j, c->cmd_w_args[j]);
		}
		printf("is file : %d\n", c->b_is_file);
		printf("\nprev tok : %d\n", c->tok_prev_token);
		printf("next tok : %d\n\n\n", c->tok_next_token);
		i++;
		c = c->next;
	}
}

void	print_values(t_data *ms)
{
	ft_printf_fd(1, "%s\n\n", PRINT_SEP_T);
	ft_printf_fd(1, "ms->user_input = %s\nms->printed_line = %s\n\n", \
	ms->user_input, ms->printed_line);
	ft_printf_fd(1, "ms->curr_wd = %s\nms->prev_w_dir = %s\n\n", \
	ms->curr_work_dir, ms->prev_work_dir);
	ft_printf_fd(1, "ms->b_temoin = %d\n", (int) ms->b_temoin);
	if (ms->parse_s->c)
		ft_cmd_display(ms, ms->parse_s->c);
	ft_printf_fd(1, "%s\n\n\n", PRINT_SEP);
}

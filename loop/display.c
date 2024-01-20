/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:43:16 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/20 19:44:25 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_display(t_cmd *cmds)
{
	int	i;

	i = 0;
	ft_printf_fd(1, "%s\n\n", PRINT_SEP_C);
	while (cmds)
	{
		ft_printf_fd(1, "cmd[%d]->raw_cmd = (d)%s(f)\n", i, cmds->raw_str);
		if (cmds->prev_token)
			ft_printf_fd(1, "prev token : (d)%s(f)\n", cmds->prev_token);
		if (cmds->next_token)
			ft_printf_fd(1, "next token : (d)%s(f)\n", cmds->next_token);
		if (cmds->cmd)
			ft_printf_fd(1, "cmd : (d)%s(f)\n", cmds->cmd);
		if (cmds->epured_model)
			ft_printf_fd(1, "epured_model : (d)%s(f)\n", cmds->epured_model);
		if (cmds->epured_str)
			ft_printf_fd(1, "epured_str : (d)%s(f)\n", cmds->epured_str);
		printf("\nprev tok : %d\n", cmds->tok_prev_token);
		printf("next tok : %d\n\n\n", cmds->tok_next_token);
		i++;
		cmds = cmds->next;
	}
}

/* to delete in the future */
void	print_values(t_data *ms)
{
	ft_printf_fd(1, "%s\n\n", PRINT_SEP_T);
	ft_printf_fd(1, "ms->user_input = %s\nms->printed_line = %s\n\n", \
	ms->user_input, ms->printed_line);
	ft_printf_fd(1, "ms->curr_wd = %s\nms->prev_w_dir = %s\n\n", \
	ms->curr_work_dir, ms->prev_work_dir);
	ft_printf_fd(1, "ms->b_temoin = %d\n", (int) ms->b_temoin);
	if (ms->parse_struct->struct_cmds)
		ft_cmd_display(ms->parse_struct->struct_cmds);
	ft_printf_fd(1, "%s\n\n\n", PRINT_SEP);
}

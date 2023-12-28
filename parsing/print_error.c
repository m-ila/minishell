/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:51:09 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 23:13:25 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
type == s : syntax error
type == m : print message
*/
void	ft_msg_end(char *str, char type, bool del_struct, t_parse *ms)
{
	if (type == 's')
		ft_printf_fd(2, "%s%s'\n", SYNTAX_ERR, str);
	if (type == 'm')
		ft_printf_fd(2, "minishell: error: %s\n", str);
	if (del_struct)
		ft_free_all(ms);

}

void	ft_free_cmds(t_cmd **cmds)
{
	t_cmd	*buff;

	if (!cmds)
		return ;
	while (*cmds)
	{
		buff = *cmds;
		*cmds = (*cmds)->next;
		if (buff->cmd)
			free(buff->cmd);
		if (buff->cmd_w_arg)
			ft_free_2d_array(buff->cmd_w_arg);
		if (buff->cmd_w_arg)
		{
			free(buff->cmd_w_arg);
			buff->cmd_w_arg = NULL;
		}
		free(buff);
	}
}

void	ft_free_all(t_parse *ms)
{
	if (ms->arr_token)
		ft_free_2d_array(ms->arr_token);
	if (ms->arr_input)
		ft_free_2d_array(ms->arr_input);
	if (ms->env_struct)
		ft_env_free(ms->env_struct->node_);
	if (ms->cmds)
		ft_free_cmds(&ms->cmds);
	if (ms->data_struct)
	{
		if (ms->data_struct->cwd)
			free(ms->data_struct->cwd);
		if (ms->data_struct->prompt)
			free(ms->data_struct->prompt);
		if (ms->data_struct->input)
			free(ms->data_struct->input);
	}
}

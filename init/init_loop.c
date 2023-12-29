/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/29 17:59:45 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_malloc_s_parse(t_data *ms)
{
	t_parse	*parse_struct;

	parse_struct = malloc(sizeof(t_parse));
	if (!parse_struct)
	{
		ft_printf_fd(2, "malloc struct parse failed\n");
		return (false);
	}
	parse_struct->token_nb = 0;
	parse_struct->start_w_val_tok = false;
	parse_struct->struct_cmds = NULL;
	ms->parse_struct = parse_struct;
	return (true);
}

bool	ft_first_init(t_data *ms, char **envp)
{
	if (!ft_env_struct_init(ms, envp))
		return (false);
	ft_increment_shlvl(ms->env_struct->node_);
	if (!ft_malloc_curr_cwd(ms))
	{
		ft_env_free(ms->env_struct->node_);
		return (false);
	}
	ms->user_input = 0;
	ms->printed_line = 0;
	return (true);
}

bool	ft_malloc_curr_cwd(t_data *ms)
{
	char	*curr_work_dir;
	char	*prev_work_dir;

	curr_work_dir = ft_calloc(2, (size_t) SIZE_PATH_MAX);
	prev_work_dir = ft_calloc(2, (size_t) SIZE_PATH_MAX);
	if (!curr_work_dir || !prev_work_dir)
	{
		ft_printf_fd(2, "malloc gen cwd failed\n");
		return (false);
	}
	else
	{
		ms->curr_work_dir = curr_work_dir;
		ms->prev_work_dir = prev_work_dir;
	}
	return (true);
}

/*
void	ft_update_env_cwd(t_data *ms)
{
	if (ms->env_struct->node_)
	{

	}
}
*/

/* data->curr_work_dir est un buffer 
Est-ce que si le path quand on CD est incorrect, actualise old_pwd ? */
bool	ft_get_cwd(t_data *ms, unsigned int i)
{
	if (i == 0)
		ms->prev_work_dir = ft_strdup("");
	if (i > 0)
	{
		free(ms->prev_work_dir);
		ms->prev_work_dir = ft_strdup(ms->curr_work_dir);
	}
	if (getcwd(ms->curr_work_dir, (size_t) SIZE_PATH_MAX))
		ms->printed_line = ft_strjoin(ms->curr_work_dir, " > minishell : ");
	else
	{
		ft_printf_fd(2, "Error getting cwd with getcwd\n");
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 11:36:01 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_malloc_s_parse(t_data *ms)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	if (!p)
	{
		ft_printf_fd(2, "malloc struct parse failed\n");
		return (false);
	}
	p->start_w_val_tok = false;
	p->struct_cmds = NULL;
	p->nb_reigning_quotes = 0;
	p->l_reign_q = '.';
	p->heredoc_fd = -1;
	ft_set_char_to_null(&p->tmp_tag, &p->tmp_val, &p->tmp_str);
	ft_set_char_to_null(&p->tmp_model, &p->str1, &p->str2);
	ft_set_char_to_null(&p->str3, &p->model1, &p->model2);
	ft_set_char_to_null(&p->model3, &p->h_lim, NULL);
	ms->parse_struct = p;
	return (true);
}

bool	ft_first_init(t_data *ms, char **envp)
{
	if (!ft_env_init(envp, ms))
		return (false);
	if (!ft_increment_shlvl(ms, ms->envi))
	{
		ft_free_2d_array(ms->envi);
		return (false);
	}
	if (!ft_malloc_curr_cwd(ms))
	{
		ft_free_2d_array(ms->envi);
		return (false);
	}
	ms->user_input = NULL;
	ms->printed_line = NULL;
	ms->tmp_str = NULL;
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
to do : needs to be modified once cd builtin is set up
update oldpwd quand builtin cd is used
*/
void	ft_update_env_cwd(t_data *ms)
{
	if (!ms)
		return ;
	if (!ms->envi)
		return ;
	if (ms->envi)
		ft_actualise_env(ms, "PWD", ms->curr_work_dir);
}

/*
data->curr_work_dir est un buffer 
Est-ce que si le path quand on CD est incorrect, actualise old_pwd ?
needs to be modified once cd builtin is set up, see README
*/
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
	{
		ms->printed_line = ft_strjoin(ms->curr_work_dir, " > minishell : ");
		ft_update_env_cwd(ms);
	}
	else
	{
		ft_printf_fd(2, "Error getting cwd with getcwd\n");
		return (false);
	}
	return (true);
}

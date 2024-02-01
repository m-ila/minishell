/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:51:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/01 17:57:01 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* un free sur ms->curr_work_dir causera un leak ici avec la boucle */
void	ft_free_prompt(t_data **ms)
{
	ft_multiple_free(&(*ms)->user_input, &(*ms)->printed_line, NULL);
}

void	ft_free_loop(t_data *ms)
{
	if (ms->parse_s->c)
		ft_free_cmds(ms->parse_s->c);
	ft_multiple_free(&ms->tmp_str, &ms->parse_s->h_lim, NULL);
	ft_free_groups(ms, &ms->parse_s->gr);
	free(ms->parse_s->gr);
	free(ms->parse_s);
	ft_free_prompt(&ms);
}

void	ft_free_end(t_data *ms)
{
	ft_free_2d_array(ms->envi);
	ft_multiple_free(&ms->tmp_str, &ms->prev_work_dir, &ms->curr_work_dir);
	ft_multiple_free(&ms->printed_line, NULL, NULL);
	ft_free_groups(ms, &ms->parse_s->gr);
	free(ms->parse_s->gr);
	free(ms->parse_s);
	free(ms);
	rl_clear_history();
}

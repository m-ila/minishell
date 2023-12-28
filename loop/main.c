/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:35:48 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/28 18:02:59 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_prompt(t_data *ms)
{
	free(ms->curr_work_dir);
	free(ms->user_input);
	free(ms->printed_line);
}

void	ft_loop(t_data *ms)
{
	while (true)
	{
		if (!ft_get_curr_cwd(ms))
			return ;
		ms->user_input = readline(ms->printed_line);
		ft_printf_fd(1, "ms->user_input = %s\nms->printed_line = %s\n", \
		ms->user_input, ms->printed_line);
		add_history(ms->user_input);
		ft_free_prompt(ms);
		return ;
		//addhistory
		//premiere couche parsing
		//init struct
		//deuxieme couche parsing
		//exec
		//free_prompt (prep for the next one)
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*ms;

	(void)argc;
	(void)argv;
	ms = malloc(sizeof(t_data));
	if (!ms)
		return (R_ERR_GEN);
	if (!ft_first_init(ms, envp))
		return (R_ERR_GEN);
	ft_loop(ms);
	ft_env_free(ms->env_struct->node_);
	free(ms->env_struct);
	free(ms);
	return (0);
}

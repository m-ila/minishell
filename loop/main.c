/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:35:48 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/28 19:11:28 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* un free sur ms->curr_work_dir causera un leak ici avec la boucle */
static void	ft_free_prompt(t_data *ms)
{
	free(ms->user_input);
	free(ms->printed_line);
}

/* to delete in the future */
static void	print_values(t_data *ms)
{
	ft_printf_fd(1, "ms->user_input = %s\n\nms->printed_line = %s\n\n", \
	ms->user_input, ms->printed_line);
	ft_printf_fd(1, "ms->curr_wd = %s\nms->prev_w_dir = %s\n\n", \
	ms->curr_work_dir, ms->prev_work_dir);
}

void	ft_loop(t_data *ms)
{
	unsigned int	i;

	i = 0;
	while (true)
	{
		i++;
		if (!ft_get_cwd(ms, i))
			return ;
		/* actualise cwd in env */
		ms->user_input = readline(ms->printed_line);
		print_values(ms);
		add_history(ms->user_input);
		if (!ft_strncmp(ms->user_input, "exit", ft_strlen(ms->user_input)))
		{
			ft_free_prompt(ms);
			return ;
		}
		if (!ft_strncmp(ms->user_input, "env", ft_strlen(ms->user_input)))
			ft_env_display(&ms->env_struct->node_);
		ft_free_prompt(ms);
		//premiere couche parsing
		//init struct from user_input
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
	(void)envp;
	envp = NULL;
	ms = malloc(sizeof(t_data));
	if (!ms)
		return (R_ERR_GEN);
	if (!ft_first_init(ms, envp))
		return (R_ERR_GEN);
	ft_loop(ms);
	ft_env_free(ms->env_struct->node_);
	free(ms->env_struct);
	free(ms->prev_work_dir);
	free(ms->curr_work_dir);
	free(ms);
	return (0);
}

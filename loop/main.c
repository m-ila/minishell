/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:35:48 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/30 22:31:30 by mbruyant         ###   ########.fr       */
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
	ft_printf_fd(1, "%s\n\n", PRINT_SEP_T);
	ft_printf_fd(1, "ms->user_input = %s\nms->printed_line = %s\n\n", \
	ms->user_input, ms->printed_line);
	ft_printf_fd(1, "ms->curr_wd = %s\nms->prev_w_dir = %s\n\n", \
	ms->curr_work_dir, ms->prev_work_dir);
	ft_printf_fd(1, "parse_struct->token_nb = %d\n", ms->parse_struct->token_nb);
	ft_printf_fd(1, "ms->b_temoin = %d\n", (int) ms->b_temoin);
	if (ms->parse_struct->struct_cmds)
		ft_cmd_display(ms->parse_struct->struct_cmds);
	ft_printf_fd(1, "%s\n\n\n\n\n", PRINT_SEP);
}

/* how do deal with heredoc ? 
how to deal with sigs ? 
if !ft_malloc_s_parse END EVERYTHING : changer les return ; au debut pour un free tt
avec pour condition si existe -> implique que dans la fonction free, on free(var) puis
var = NULL 
cwd is actualise in ft_get_cwd */
void	ft_loop(t_data *ms)
{
	unsigned int	i;

	i = 0;
	while (true)
	{
		i++;
		ms->b_temoin = true;
		if (!ft_get_cwd(ms, i))
			return ;
		if (!ft_malloc_s_parse(ms))
			return ;
		ms->user_input = NULL;
//		ft_putstr_fd(ms->printed_line, 1);
		ms->user_input = readline(ms->printed_line);
		add_history(ms->user_input);
		if (ft_first_layer_parse(ms->user_input, ms) != R_EX_OK)
			ms->b_temoin = false;
		if (ms->b_temoin)
		{
			ft_cmd_struct(ms, ms->user_input);
		}
		print_values(ms);
		if (ms->b_temoin && \
		!ft_strncmp(ms->user_input, "exit\n", ft_strlen(ms->user_input)))
		{
			ft_free_cmds(ms->parse_struct->struct_cmds);
			ft_free_prompt(ms);
			return ;
		}
		if (ms->b_temoin && \
		!ft_strncmp(ms->user_input, "env\n", ft_strlen(ms->user_input)))
			ft_env_display(&ms->env_struct->node_);
		if (ms->parse_struct->struct_cmds)
		{
			ft_free_cmds(ms->parse_struct->struct_cmds);
		}
		free(ms->parse_struct);
		ft_free_prompt(ms);
		//deuxieme couche parsing
		//exec
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
	free(ms->parse_struct);
	free(ms);
	return (0);
}

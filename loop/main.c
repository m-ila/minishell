/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:35:48 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/04 09:17:37 by mbruyant         ###   ########.fr       */
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
	ft_printf_fd(1, "%s\n\n\n", PRINT_SEP);
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
		/* init cwd and pws */
		if (!ft_get_cwd(ms, i))
			return ;
		/* init parsing struct */
		if (!ft_malloc_s_parse(ms))
			return ;
		ms->user_input = NULL;
//		ft_putstr_fd(ms->printed_line, 1);
		ms->user_input = readline(ms->printed_line);
		//if heredoc, gnl jusqu'a delimiter dans la str recuperee
		add_history(ms->user_input);
		/* new first parsing lvl AND init cmd struct see parsing/tmp.c file */
		ft_raw_parsing_process(ms->user_input, ms);
		print_values(ms);
		/* temp builtins to check leaks */
		if (ms->b_temoin && \
		!ft_strncmp(ms->user_input, "exit", ft_strlen(ms->user_input)))
		{
			ft_free_cmds(ms->parse_struct->struct_cmds);
			ft_free_prompt(ms);
			return ;
		}
		/* temp builtins to check leaks */
		if (ms->b_temoin && \
		!ft_strncmp(ms->user_input, "env", ft_strlen(ms->user_input)))
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
//	g_return_val = 0;
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

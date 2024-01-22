/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:35:48 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 11:25:26 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_return_val;

/* un free sur ms->curr_work_dir causera un leak ici avec la boucle */
void	ft_free_prompt(t_data **ms)
{
	ft_multiple_free(&(*ms)->user_input, &(*ms)->printed_line, NULL);
}

/* how do deal with heredoc ? 
how to deal with sigs ? 
if !ft_malloc_s_parse END EVERYTHING : changer les return ; 
au debut pour un free tt
avec pour condition si existe -> implique que dans la fonction free, 
on free(var) puis
var = NULL 
cwd is actualise in ft_get_cwd */
void	ft_loop(t_data *ms)
{
	unsigned int	i;

	i = 0;
	while (true)
	{
		i++;
		if (!ft_comp_var_env(g_return_val, ms))
			return ;
		ms->b_temoin = true;
		/* init cwd and pws */
		if (!ft_get_cwd(ms, i))
			return ;
		/* init parsing struct */
		if (!ft_malloc_s_parse(ms))
			return ;
		ms->user_input = NULL;
		ms->user_input = readline(ms->printed_line);
		if (!ms->user_input)
			return ;
		if (ms->user_input && ft_strlen(ms->user_input) == 0)
			ms->b_temoin = false;
		//if heredoc, gnl jusqu'a delimiter dans la str recuperee
		add_history(ms->user_input);
		if (ms->b_temoin)
			ft_count_reigning_quotes(ms->user_input, ms->parse_struct);
		if (ms->b_temoin && ms->parse_struct->nb_reigning_quotes % 2 != 0)
		{
			ft_msg("", 'q', false, ms);
			ms->b_temoin = false;
		}
		ft_raw_parsing_process(ms->user_input, ms);
		print_values(ms);
		if (ms->b_temoin && !ms->parse_struct->struct_cmds->cmd)
			ms->b_temoin = false;
		if (ms->parse_struct->struct_cmds->tok_next_token == heredoc)
		{
			ms->parse_struct->h_lim = ft_strdup(ms->parse_struct->struct_cmds->next->cmd);
			ft_heredoc(ms, ms->parse_struct);
			free(ms->parse_struct->h_lim);
		}
		if (ms->b_temoin && ft_is_builtin(ms->parse_struct->struct_cmds->cmd))
			if (ft_builtin(ms->parse_struct->struct_cmds, ms) != R_EX_OK)
				ms->b_temoin = false;
		if (ms->parse_struct->struct_cmds)
		{
			ft_free_cmds(ms->parse_struct->struct_cmds);
		}
		ft_multiple_free(&ms->tmp_str, NULL, NULL);
		free(ms->parse_struct);
		ft_free_prompt(&ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*ms;

	(void)argc;
	(void)argv;
	(void)envp;
	envp = NULL;
	g_return_val = 0;
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	ms = malloc(sizeof(t_data));
	if (!ms)
		return (R_ERR_GEN);
	if (!ft_first_init(ms, envp))
		return (R_ERR_GEN);
	ft_loop(ms);
	ft_free_2d_array(ms->envi);
	ft_multiple_free(&ms->tmp_str, &ms->prev_work_dir, &ms->curr_work_dir);
	ft_multiple_free(&ms->printed_line, NULL, NULL);
	free(ms->parse_struct);
	free(ms);
	rl_clear_history();
	return (g_return_val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:35:48 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/02 17:27:59 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_return_val;

void	ft_loop(t_data *ms)
{
	unsigned int	i;

	i = 0;
	while (true)
	{
		i++;
//		printf("g_ret_val_debut : %d\n", g_return_val);
		if (!ft_comp_var_env(ms))
			return ;
		ms->b_temoin = true;
		if (!ft_get_cwd(ms, i))
			return ;
		if (!ft_malloc_s_parse(ms))
			return ;
		ms->user_input = NULL;
		ms->user_input = readline(ms->printed_line);
		if (!ms->user_input)
			return ;
		if (ms->user_input && ft_strlen(ms->user_input) == 0)
			ms->b_temoin = false;
		add_history(ms->user_input);
		if (ms->b_temoin)
			ft_count_reigning_quotes(ms->user_input, ms->parse_s);
		if (ms->b_temoin && ms->parse_s->nb_reigning_quotes % 2 != 0)
		{
			ft_msg("", 'q', false, ms);
			ms->b_temoin = false;
		}
		ft_raw_parsing_process(ms->user_input, ms);
		ft_groups(ms, ms->parse_s);
		print_values(ms);
		if (ms->b_temoin && !ms->parse_s->c->cmd)
			ms->b_temoin = false;
		if (ms->b_temoin && ft_is_builtin(ms->parse_s->c->cmd))
			if (ft_builtin(ms->parse_s->c, ms) != R_EX_OK)
				ms->b_temoin = false;
		ft_free_loop(ms);
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
	ft_free_end(ms);
	return (g_return_val);
}

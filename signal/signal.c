/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:51:00 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/20 11:26:47 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_r_val(int val, t_data *ms)
{
	char	*str_val;

	g_return_val = val;
	str_val = ft_itoa(g_return_val);
	if (!val)
		ft_msg("failed to change return val", 'm', false, NULL);
	ft_actualise_env(ms, "$", str_val);
	free(str_val);
	return ;
}

void	ft_comp_var_env(int val, t_data *ms)
{
	char	*str_val;
	int		int_val;

	str_val = ft_get_val_in_env(ms->envi, "$", ms);
	if (!str_val || str_val[0] == '\0')
	{
		ft_multiple_free(&str_val, NULL, NULL);
		return ;
	}
	int_val = ft_atoi(str_val);
	if (int_val != val && val >= 0)
		ft_set_r_val(int_val, ms);
	ft_multiple_free(&str_val, NULL, NULL);
}

/*
quand heredoc, ouvrir le fd puis mettre g_return_val = -fd
puis, quand close, mettre g_return_val = valeur in env
(n'a pas été changé lors de -fd)
*/
void	ft_ctrl_c(int val)
{
	(void)val;
	if (g_return_val < 0)
	{
		ft_printf_fd(2, "^C\n");
		close(-g_return_val);
	}
	else
	{
		ft_printf_fd(2, "\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_return_val = R_CTRL_C;
}

void	ft_ctrl_d(int val)
{
	(void)val;
	g_return_val = R_CTRL_D;
	ft_printf_fd(2, "Quit (core dumped)\n");
}

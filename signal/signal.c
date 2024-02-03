/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:51:00 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 14:46:18 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_reset_global(t_data *ms)
{
	char	*str_val;
	int		val;

	str_val = ft_get_val_in_env(ms->envi, "?", ms);
	if (!str_val)
		return (ft_msg("failed to get return val", 'm', false, ms));
	val = ft_atoi(str_val);
	g_return_val = val;
	free(str_val);
}

void	ft_set_r_val(int val, t_data *ms)
{
	char	*str_val;

	g_return_val = val;
	str_val = ft_itoa(g_return_val);
	if (!str_val)
		return (ft_msg("failed to change return val", 'm', false, NULL));
	ft_actualise_env(ms, "?", str_val);
	free(str_val);
}

bool	ft_comp_var_env(t_data *ms)
{
	char	*str_val;
	int		int_val;

	str_val = ft_get_val_in_env(ms->envi, "?", ms);
	if (!str_val || str_val[0] == '\0')
		return (ft_free_return(&str_val, NULL, NULL, false));
	int_val = ft_atoi(str_val);
	if (int_val != g_return_val && int_val >= 0)
		ft_set_r_val(g_return_val, ms);
	return (ft_free_return(&str_val, NULL, NULL, true));
}

void	ft_ctrl_c(int val)
{
	int	tmp;

	(void)val;
	if (g_return_val < 0)
	{
		ft_printf_fd(2, "\n");
		tmp = -g_return_val;
		g_return_val = -1;
		close(tmp);
	}
	else
	{
		g_return_val = R_CTRL_C;
		ft_printf_fd(2, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

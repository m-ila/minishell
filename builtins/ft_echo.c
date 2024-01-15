/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:40:41 by chourael          #+#    #+#             */
/*   Updated: 2024/01/15 18:49:55 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
to do : voir avec Chourael si print sur sortie standard OK si redirections
sinon changer FD dans ft_printf_fd et write
*/
int	ft_echo(t_cmd *cmds)
{
	int	i;
	int	n;
	int	len;

	if (!cmds)
		return (R_ERR_GEN);
	i = 1;
	n = 0;
	len = ft_2d_lines(cmds->cmd_w_arg);
	if (len > 1)
	{
		if (!ft_strncmp(cmds->cmd_w_arg[1], "-n", ft_strlen("-n ")))
			n = 1;
		while (cmds->cmd_w_arg[i + n])
		{
			ft_printf_fd(1, "%s", cmds->cmd_w_arg[i + n]);
			if (i + n < len - 1)
				ft_printf_fd(1, " ");
			i++;
		}
		if (n == 0)
			ft_printf_fd(1, "\n");
	}
	return (R_EX_OK);
}

/*
to do : should b->temoin = false if fail ?
*/
char	*ft_triple_join(char *str1, char *str2, char *str3, t_data *ms)
{
	char	*buff1;
	char 	*finale;

	if (!str1 || !str2 || !str3 || !ms)
		return (ft_strdup(""));
	buff1 = ft_strjoin(str1, str2);
	if (!buff1)
		return (ft_char_print_msg("str triple join", 'm', NULL, ms));
	finale = ft_strjoin(buff1, str3);
	if (!finale)
	{
		free(buff1);
		return (ft_char_print_msg("str triple join", 'm', NULL, ms));
	}
	free(buff1);
	return (finale);
}

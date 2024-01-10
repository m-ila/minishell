/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:40:41 by chourael          #+#    #+#             */
/*   Updated: 2024/01/10 14:59:46 by mbruyant         ###   ########.fr       */
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

	if (!cmds)
		return (R_ERR_GEN);
	i = 1;
	n = 0;
	if (!ft_strncmp(cmds->cmd_w_arg[1], "-n", ft_strlen("-n")))
		n = 1;
	while (cmds->cmd_w_arg[i + n])
	{
		ft_printf_fd(1, "%s", cmds->cmd_w_arg[i + n]);
		i++;
	}
	if (n == 0)
		ft_printf_fd(1, "\n");
	return (R_EX_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:55:56 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 22:59:53 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_is_valid_cmd(char *str)
{
	if (!str || !*str)
		return (false);
	if (ft_only_sep_base(str, "\n\t "))
		return (false);
	return (true);
}
/*
int	ft_get_valid_cmd_nb(char **cmd_arr)
{
	int	i;
	int	nb;

	if (!cmd_arr)
		return (0);
	if (*cmd_arr == '\0')
		return (-1);
	i = 0;
	nb = 0;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:25:17 by chourael          #+#    #+#             */
/*   Updated: 2024/01/10 13:33:38 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char *str)
{
	if (str == NULL || str[0] == '\0' || str[0] == '~')
	{
		if (chdir(getenv("HOME")) == -1)
		{
			perror("chdir 1");
			return (-1);
		}
	}
	else if (chdir(str) == -1)
	{
		perror("chdir 0");
		return (-1);
	}
	return (0);
}

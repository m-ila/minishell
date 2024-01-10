/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchour <chchour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:15:21 by chchour           #+#    #+#             */
/*   Updated: 2024/01/04 14:18:08 by chchour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_cpymalloc(char **envcpy, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		envcpy[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (envcpy[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

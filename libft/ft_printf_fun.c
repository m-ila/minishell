/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:57:32 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 11:54:43 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_str(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printf_char(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

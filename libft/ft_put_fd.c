/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:40:15 by mbruyant          #+#    #+#             */
/*   Updated: 2023/10/11 16:36:12 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	limite;
	int	conv;

	limite = 0;
	if (n >= 0 && n <= 9)
	{
		conv = n + '0';
		ft_putchar_fd(conv, fd);
	}
	else if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		limite = 1;
	}
	else if (n < 0 && limite == 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9 && limite == 0)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (ft_strlen(s) > 0)
		write(fd, s, ft_strlen(s));
}

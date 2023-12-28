/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:03:15 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 11:54:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_hex(unsigned int nb, const char type, int fd)
{
	if (nb >= 16)
	{
		ft_print_hex(nb / 16, type, fd);
		ft_print_hex(nb % 16, type, fd);
	}
	if (nb <= 9)
		ft_putchar_fd((nb + '0'), fd);
	if (nb >= 10 && nb < 16)
	{
		if (type == 'x')
			ft_putchar_fd((nb - 10 + 'a'), fd);
		if (type == 'X')
			ft_putchar_fd((nb - 10 + 'A'), fd);
	}
}

static int	ft_hex_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		nb = nb / 16;
		len++;
	}
	return (len);
}

int	ft_printf_hex(unsigned int nb, const char type, int fd)
{
	if (nb == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	else
		ft_print_hex(nb, type, fd);
	return (ft_hex_len(nb));
}

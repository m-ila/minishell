/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:03:54 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/25 21:25:56 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(long int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int	ft_printf_nb(long int nb, int fd)
{
	ft_putnbr_fd(nb, fd);
	return (ft_count_digits(nb));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:22:05 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/25 21:25:44 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_type(va_list args, const char type, int fd)
{
	int	retour;

	retour = 0;
	if (type == 'c')
		retour += ft_printf_char(va_arg(args, int), fd);
	if (type == 's')
		retour += ft_printf_str(va_arg(args, char *), fd);
	if (type == 'x' || type == 'X')
		retour += ft_printf_hex(va_arg(args, int), type, fd);
	if (type == 'd' || type == 'i')
		retour += ft_printf_nb(va_arg(args, int), fd);
	if (type == 'u')
		retour += ft_printf_uns(va_arg(args, unsigned int), fd);
	if (type == '%')
		retour += ft_printf_char('%', fd);
	if (type == 'p')
		retour += ft_printf_ptr(va_arg(args, unsigned long long int), fd);
	return (retour);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		retour;
	int		i;

	i = 0;
	retour = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			retour += ft_type(args, str[i + 1], fd);
			i++;
		}
		else
			retour += ft_printf_char(str[i], fd);
		i++;
	}
	va_end(args);
	return (retour);
}

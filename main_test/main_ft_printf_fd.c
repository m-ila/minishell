/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_printf_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:19:47 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 12:30:06 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/ft_printf_fd/ft_printf_fd.h"
#include "../includes/minishell.h"

int	main(void)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	str = ft_strdup("coucou");
	fd = open("file.tmp", O_RDWR | O_TRUNC | O_CREAT, 000644);
	while (i < 5)
	{
		ft_printf_fd(i, "%d\n%s\n%x\n", i, str, str);
		i++;
	}
	close(fd);
	free(str);
	return (0);
}

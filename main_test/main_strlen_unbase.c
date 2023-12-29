/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strlen_unbase.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:01:29 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/29 13:05:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	if (!argc)
		return (0);
	ft_printf_fd(1, "input :%s\nbase : %s\nfrom : %d\nlen : %d\n", argv[1], \
	argv[2], ft_atoi(argv[3]), ft_strlen_unbase(argv[1], argv[2], \
	ft_atoi(argv[3])));
}

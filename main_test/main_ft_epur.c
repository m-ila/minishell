/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_epur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:11:28 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 16:40:24 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc > 2)
	{
		char	*str = argv[1];
		char	to_epur = argv[2][0];
		char	*ret = ft_str_epur(str, to_epur);
		char	**retret = ft_copy_2d_array(envp, 0, ft_2d_lines(envp));
		int		i = 0;
		
		if (!ret || !retret)
			return (ft_printf_fd(2, "malloc error\n"));
		ft_printf_fd(1, "==== ft_str_epur ====\n");
		ft_printf_fd(1, "%s\n", ret);
		ft_printf_fd(1, "\n\n\n==== ft_arr_epur ====\n");
		ft_printf_fd(1, "==== envp before ====\n");
		while (retret[i])
		{
			ft_printf_fd(1, "%s\n", retret[i]);
			i++;
		}
		ft_printf_fd(1, "\n\n\n==== envp after ====\n");
		i = 0;
		ft_arr_epur(retret, argv[3][0]);
		while (retret[i])
		{
			ft_printf_fd(1, "%s\n", retret[i]);
			i++;
		}
		free(ret);
		ft_free_2d_array(retret);
	}
	return (0);
}

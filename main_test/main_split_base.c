/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_split_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:54:36 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/25 19:16:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	char	**ar_tokens;
	char	**ar_cmds;
	int		i;
	int		j;

	if (!argc)
		return (0);
	ar_tokens = ft_split_unbase(argv[1], BASE_TOKEN);
	ar_cmds = ft_split_base(argv[1], BASE_TOKEN);
	i = 0;
	j = 0;
	if (!ar_tokens || !ar_cmds)
		return (printf("Error split\n"));
	while (ar_tokens[i])
	{
		printf("index %d\tvalue ar_tokens : %s\n", i, ar_tokens[i]);
		i++;
	}
	while (ar_cmds[j])
	{
		printf("index %d\tvalue ar_cmds : %s\n", j, ar_cmds[j]);
		j++;
	}
	ft_free_2d_array(ar_tokens);
	ft_free_2d_array(ar_cmds);
	return (0);
}

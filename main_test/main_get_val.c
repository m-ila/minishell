/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:02:27 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/06 18:09:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
char	*ft_get_val_in_env(char **env, char *tag, t_data *ms);

int	main(int argc, char **argv, char **envp)
{
	t_data	*ms;

	ms = malloc(sizeof(*ms));
	if (argc && argv)
		printf("%s\n", ft_get_val_in_env(envp, "PWD", ms));
	return (0);
}

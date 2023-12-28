/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:44:13 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/23 21:47:30 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	/*char *env_ex[] = {
		NULL
	};*/

/* to test leaks if envp null
	envp = NULL; */
	t_env *myEnv = ft_init_envi(envp);
	if (myEnv && argc >= 3)
	{
		printf("Initial Environment:\n");
 		ft_env_display(&(myEnv->node_));
		printf("\n");
		ft_env_update(myEnv->node_, argv[1], argv[2]);
		printf("Updated Environment:\n");
		ft_env_display(&(myEnv->node_));
		printf("\n");
		ft_env_free(myEnv->node_);
		free(myEnv);
	}
	else
		printf("nothing in env \n");
	return 0;
}

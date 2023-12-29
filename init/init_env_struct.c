/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:59:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/29 17:55:30 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_env_struct_init(t_data *ms, char **envp)
{
	t_env	*env_struct;

	env_struct = ft_init_envi(envp);
	if (!env_struct)
	{
		ft_printf_fd(2, "Gen of env_struct failed\n");
		return (false);
	}
	else
		ms->env_struct = env_struct;
	return (true);
}

/* IF DOESN'T FIND THE NODE (used right after init, 
so in case of unset SHLVL before) SHOULD WE CREATE ONE ? */
void	ft_increment_shlvl(t_env_node *envi)
{
	int			shlvl_value;
	t_env_node	*shlvl_node;

	shlvl_node = ft_get_node(envi, "SHLVL");
	if (!shlvl_node)
		return (ft_msg_end("couldn't fetch the node", 'm', false, NULL));
	shlvl_value = ft_atoi(shlvl_node->n_content);
	shlvl_value++;
	free(shlvl_node->n_content);
	shlvl_node->n_content = ft_itoa(shlvl_value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:27:10 by chourael          #+#    #+#             */
/*   Updated: 2024/01/25 16:11:29 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_data *ms, t_cmd *c)
{
	if (!ms || !ms->envi)
		return (R_ERR_GEN);
	if (ft_2d_lines(c->all_elem) > 1)
		return (R_EX_OK);
	ft_env_display(ms);
	return (R_EX_OK);
}

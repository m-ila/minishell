/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:10:48 by chourael          #+#    #+#             */
/*   Updated: 2024/01/10 14:02:34 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_data *ms)
{
	if (!ms || !ms->curr_work_dir)
		return (R_ERR_GEN);
	ft_printf_fd(1, "%s\n", ms->curr_work_dir);
	return (R_EX_OK);
}

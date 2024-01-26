/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:31:48 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/26 15:59:55 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_set_val_ret(t_data *ms, bool ret)
{
	ms->b_temoin = false;
	return (ret);
}

bool	ft_redir_io_token(t_tokens t)
{
	return (t == redir_in || t == redir_out || \
	t == redir_out_app || t == heredoc);
}

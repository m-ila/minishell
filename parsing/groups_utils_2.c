/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:55:02 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/28 14:08:51 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_is_input_redirect(t_tokens t)
{
	return (t == heredoc || t == redir_in);
}

bool	ft_is_output_redirect(t_tokens t)
{
	return (t == redir_out || t == redir_out_app);
}

bool	ft_is_io_redirect(t_tokens t)
{
	return (t == heredoc || t == redir_in || t == redir_out || t == redir_out_app);
}

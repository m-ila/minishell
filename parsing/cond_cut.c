/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond_cut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:07:19 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/20 19:08:39 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_cond_cut(char *str, int i)
{
	if (ft_char_is_a_reigning_quote(str, i))
		return (true);
	if (ft_char_in_base(str[i], BASE_QUOTES) && \
	ft_elem_is_in_quotes(str, i) == NOT_QUOTED)
		return (true);
	if (ft_char_in_base(str[i], " ") && \
	ft_elem_is_in_quotes(str, i) == NOT_QUOTED)
		return (true);
	return (false);
}

bool	ft_cut_only_quotes(char *str, int i)
{
	if (ft_char_is_a_reigning_quote(str, i))
		return (true);
	if (ft_char_in_base(str[i], BASE_QUOTES) && \
	ft_elem_is_in_quotes(str, i) == NOT_QUOTED)
		return (true);
	return (false);
}

bool	ft_export_cond_cut(char *str, int i)
{
	if (i > 0 && ft_char_is_a_reigning_quote(str, i - 1) && \
	(!str[i] || ft_iswhitespace(str[i])))
		return (true);
	if (ft_iswhitespace(str[i]) && \
	ft_elem_is_in_quotes(str, i) == NOT_QUOTED)
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:15:41 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 11:31:38 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_is_valid_token(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 2 || len == 0)
		return (false);
	if (len == 1)
		return (ft_char_in_base(*str, BASE_TOKEN));
	if (str[0] != str[1] || ft_strocc_unbase(str, "<>"))
		return (false);
	return (true);
}

/* first token should be < > << >> */
bool	ft_is_valid_entry_token(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 2 || len == 0)
		return (false);
	if (len == 1)
		return (ft_char_in_base(*str, "<>"));
	if (str[0] != str[1] || ft_strocc_unbase(str, "<>"))
		return (false);
	return (true);
}

bool	ft_starts_with_token(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i] && ft_iswhitespace(user_input[i]))
		i++;
	if (user_input[i] == '\0')
		return (false);
	if (ft_char_in_base(user_input[i], BASE_TOKEN))
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:45:08 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/28 21:20:06 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* returns the index of the next token or end of line */
int	ft_get_next_token_index(char *user_input, int from)
{
	if (!user_input)
		return (NULL);
	if (from >= ft_strlen(user_input))
		return (-1);
	while (user_input[from] && !ft_char_in_base(user_input[from], BASE_TOKEN))
		from++;
	return (from);
}

/* strlen_unbase renvoie quoi si arrive a la fin de ligne ? */
int	ft_starts_with_valid_token(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i] && ft_iswhitespace(user_input[i]))
		i++;
	if (user_input[i] == '\0')
		return (0);
	if (ft_strlen_unbase(user_input, BASE_TOKEN, i) > 2)
		return (-1);
	if (!ft_char_in_base(user_input[i], BASE_TOKEN))
		return (/*don't start with token*/)
}

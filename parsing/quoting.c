/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:26:08 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/29 21:08:27 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_str_has_quotes(char *user_input)
{
	int	occ;

	if (!user_input || !*user_input)
		return (false);
	occ = ft_strocc(user_input, '\'');
	occ += ft_strocc(user_input, '\"');
	if (occ > 0)
		return (true);
	return (false);
}

/* find index first quote(char **array, int from) */
/* find index last quote(char **array, char quote, int from)*/

/* 
WILL LEAK IN CASE OF BAD MALLOC, TO BE FIXED 
line : if (!q_substr || !buff)
needs to free what has been previously malloced
*/
char	*ft_expand_quoted_substr(char **array, char quote, int from, int until)
{
	int		len_array;
	char	*q_substr;
	char	*buff;

	if (!array || !*array || !ft_char_in_base(quote, BASE_QUOTES) || \
	until >= from)
		return (NULL);
	len_array = ft_2d_lines(array);
	if (until >= len_array || from >= len_array)
		return (NULL);
	while (from < until)
	{
		buff = ft_strdup(array[from]);
		if (!q_substr)
			q_substr = buff;
		if (!q_substr || !buff)
			return (ft_msg_ret_char("failed to expand quoted substr"));
		else
			q_substr = ft_strjoin(buff, array[from]);
		free(buff);
		from++;
	}
	return (q_substr);
}

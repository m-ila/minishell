/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:26:08 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/11 10:18:55 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Basically returns the value of an "until" for a substr
returns -1 in case of error
*/
int	get_next_token(char *str, int from)
{
	int		occ_rule;
	char	quoting_rule;

	if (from >= (int) ft_strlen(str) || from < 0 || !str)
		return (-1);
	quoting_rule = '.';
	occ_rule = 0;
	while (str[from])
	{
		if (ft_char_in_base(str[from], BASE_QUOTES))
		{
			if (quoting_rule == '.')
				quoting_rule = str[from];
			if (str[from] == quoting_rule)
				occ_rule++;
		}
		if (ft_char_in_base(str[from], BASE_TOKEN) && occ_rule % 2 == 0)
			return (from);
		from++;
	}
	if (from == (int) ft_strlen(str))
		return (from);
	return (-1);
}

/* TO DO : send err msg */
t_tokens	*ft_token_array(char *user_input)
{
	int			i;
	int			i_next_token;
	t_tokens	*array;
	t_tokens	quoting_rule;

	array = malloc((ft_strlen(user_input) + 1) * sizeof(*array));
	if (!array)
		return (NULL);
	i = 0;
	i_next_token = get_next_token(user_input, i);
	while (i < (int) ft_strlen(user_input))
	{
		if (i == i_next_token)
			i_next_token = get_next_token(user_input, i);
		array[i] = ft_what_token(user_input[i], quoting_rule, i, i_next_token);
		i++;
	}
	array[i] = end_of_file;
	return (array);
}

t_tokens	ft_get_quoting_rule(char *user_input, int from, int until)
{
	if (from >= until || from < 0 || until < 0 || \
	from >= ft_strlen(user_input) || until >= ft_strlen(user_input))
		return (NULL);
	while (user_input[from] && !ft_char_in_base(user_input[from], BASE_QUOTES) \
	&& from <= until)
		from++;
	if (user_input[from] == S_QUOTE)
		return (single_quote);
	if (user_input[from] == D_QUOTE)
		return (double_quote);
	return (NULL);
}

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

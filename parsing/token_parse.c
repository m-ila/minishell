/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:15:41 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/01 15:14:56 by mbruyant         ###   ########.fr       */
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

/* if all are valids, return nb of it, if not returns 0
Si aucun token, entree valide, renvoie -1
NOTE : DOIT AFFICHER MESSAGE D'ERREUR ICI */
int	ft_get_valid_token_nb(char **token_arr, t_data *ms)
{
	int	i;
	int	nb;

	if (!token_arr)
		return (0);
	if (!*token_arr)
		return (-1);
	i = 0;
	nb = 0;
	if (ft_starts_with_token(ms->user_input) && !ft_is_valid_entry_token(token_arr[0]))
			return (ft_print_msg(token_arr[0], 's', 0, ms));
	while (token_arr[i])
	{
		if (!ft_is_valid_token(token_arr[i]))
			return (ft_print_msg(token_arr[i], 's', 0, ms));
		if (ft_is_valid_token(token_arr[i]))
			nb++;
		i++;
	}
	return (nb);
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

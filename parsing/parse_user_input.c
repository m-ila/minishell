/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:45:08 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/01 15:01:59 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
if !nb_token : has invalids token(s), error printed in get_valid_token_nb
				free prompt struct
if nb_token == -1 : has no token in user_input
else : has that amount of correct token (testing only their writing and not
		their position in the str !!!)

PARSE STRUCT NEEDS TO BE INITIALIZED BEFORE
*/
int	ft_first_layer_parse(char *user_input, t_data *ms)
{
	char	**arr_token;
	int		nb_token;

	arr_token = ft_split_unbase(user_input, BASE_TOKEN);
	if (!arr_token)
		return (ft_print_msg("malloc error gen arr token", 'm', R_ERR_GEN, ms));	
	nb_token = ft_get_valid_token_nb(arr_token, ms);
	if (!nb_token)
		ms->b_temoin = false;
	else if (nb_token == -1)
		ms->parse_struct->token_nb = 0;
	else if (nb_token > 0)
		ms->parse_struct->token_nb = nb_token;
	ft_free_2d_array(arr_token);
	return (R_EX_OK);
}

/* returns the index of the next token or end of line */
int	ft_get_next_token_index(char *user_input, int from)
{
	if (!user_input)
		return (-1);
	if (from >= (int) ft_strlen(user_input))
		return (-1);
	while (user_input[from] && ft_char_in_base(user_input[from], BASE_TOKEN))
		from++;
	while (user_input[from] && !ft_char_in_base(user_input[from], BASE_TOKEN))
		from++;
	return (from);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   former_parse_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:45:08 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 11:36:28 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* if all are valids, return nb of it, if not returns 0
Si aucun token, entree valide, renvoie -1
NOTE : DOIT AFFICHER MESSAGE D'ERREUR ICI */
/*
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
*/

/*
int	ft_parse_cmds_vs_tokens(int nb_tokens, int nb_cmds)
{
	if (nb_tokens == -1)
		return (R_EX_OK);
	if (nb_tokens > 0 && nb_tokens != nb_cmds - 1)
}
*/
/* retourne un code erreur ou non, si !ft_parse_input, correct 
init dans t_parse arr_token et arr_cmds */
/*
int	ft_parse_input(char *str, t_parse *ms)
{
	char	**arr_token;
	char	**arr_cmds;
	int		nb_tokens;

	arr_token = ft_split_unbase(str, BASE_TOKEN);
	arr_cmds = ft_split_base(str, BASE_TOKEN);
	if (!arr_token || !arr_cmds)
	{
		ft_printf_fd(2, "malloc error ft_parse_input\n");
		return (R_ERR_GEN);
	}
	nb_tokens = ft_get_valid_token_nb(arr_token, str);
	if (!nb_tokens)
	{
//		ft_free_prompt_data(ms);
		return (R_ERR_SH_B);
	}
	ms->arr_token = ft_copy_2d_array(arr_token, 0, ft_2d_lines(arr_token));
	ms->arr_input = ft_copy_2d_array(arr_cmds, 0, ft_2d_lines(arr_cmds));
	ms->token_nb = nb_tokens;
	ft_free_2d_array(arr_token);
	ft_free_2d_array(arr_cmds);
//	ft_parse_cmds_vs_tokens(nb_tokens);
	return (R_EX_OK);
}
*/

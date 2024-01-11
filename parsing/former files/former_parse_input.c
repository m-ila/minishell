/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   former_parse_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:45:08 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/30 18:44:15 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

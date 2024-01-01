/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_u_i_related.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:25:07 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/01 16:11:21 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
split protec : if !user_input returns NULL,
if !*user_input return char ** vide : verifier si cause leaks 
TO DO : if error variable globale = erreur
*/
int    ft_init_arr(t_data *ms, char *user_input)
{
    char    **cmd_subarr;
    char    **token_subarr;
    
    cmd_subarr = ft_split_base(user_input, BASE_TOKEN);
    if (!cmd_subarr)
        return (ft_print_msg(ERR_GEN_M_CMDS, 'm', R_ERR_GEN, ms));
    token_subarr = ft_split_unbase(user_input, BASE_TOKEN);
    if (!token_subarr)
    {
        ft_free_2d_array(cmd_subarr);
        return (ft_print_msg(ERR_GEN_M_TKS, 'm', R_ERR_GEN, ms));
    }
    ms->arr_input = cmd_subarr;
    ms->arr_token = token_subarr;
    return (R_EX_OK);
}

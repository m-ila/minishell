/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:49:06 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 11:36:44 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Note : dernier tok_next_token devra etre ajuste en fonction de la cmd
et de son previous token too (?)
*/
bool    ft_add_token_val_to_struct(t_cmd *cmds)
{
    if (!cmds)
        return (false);
    while (cmds)
    {
        cmds->tok_prev_token = ft_which_redir_token(cmds->prev_token, 'p');
        cmds->tok_next_token = ft_which_redir_token(cmds->next_token, 'n');
        cmds = cmds->next;
    }
    return (true);
}

/*
Note : dernier tok_next_token devra etre ajuste en fonction de la cmd
et de son previous token too (?)
*/
t_tokens    ft_which_redir_token(char *str, char which)
{
    if (!ft_strncmp(str, "<", ft_strlen(str)))
        return (redir_in);
    else if (!ft_strncmp(str, ">", ft_strlen(str)))
        return (redir_out);
    else if (!ft_strncmp(str, "<<", ft_strlen(str)))
        return (heredoc);
    else if (!ft_strncmp(str, ">>", ft_strlen(str)))
        return (redir_out_app);
    else if (!ft_strncmp(str, "|", ft_strlen(str)))
        return (pipe_);
    else if (!ft_strlen(str))
    {
        if (which == 'p')
            return (redir_in);
        if (which == 'n')
            return (end_of_file);
    }
    return (error);
}

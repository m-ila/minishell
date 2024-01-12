/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:15:41 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/12 15:58:17 by mbruyant         ###   ########.fr       */
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

/*
Note : dernier tok_next_token devra etre ajuste en fonction de la cmd
et de son previous token too (?)
*/
bool	ft_add_token_val_to_struct(t_cmd *cmds)
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
t_tokens	ft_which_redir_token(char *str, char which)
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

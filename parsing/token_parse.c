/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:15:41 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 17:04:03 by mbruyant         ###   ########.fr       */
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
	if (user_input[i] == '\0')
		return (false);
	if (ft_char_in_base(user_input[i], BASE_TOKEN))
		return (true);
	return (false);
}

bool	ft_add_token_val_to_struct(t_node *c)
{
	if (!c)
		return (false);
	while (c)
	{
		c->tok_prv_tok = ft_which_redir_token(c->prev_tok, 'p');
		c->tok_nxt_tok = ft_which_redir_token(c->next_tok, 'n');
		c = c->next;
	}
	return (true);
}

t_tokens	ft_which_redir_token(char *str, char which)
{
	if (!str)
		return (error);
	if (!ft_strncmp(str, "<", ft_strlen(str) + 1))
		return (redir_in);
	else if (!ft_strncmp(str, ">", ft_strlen(str) + 1))
		return (redir_out);
	else if (!ft_strncmp(str, "<<", ft_strlen(str) + 1))
		return (heredoc);
	else if (!ft_strncmp(str, ">>", ft_strlen(str) + 1))
		return (redir_out_app);
	else if (!ft_strncmp(str, "|", ft_strlen(str) + 1))
		return (pipe_);
	else if (!ft_strlen(str))
	{
		if (which == 'p')
			return (start);
		if (which == 'n')
			return (end_input);
	}
	return (error);
}

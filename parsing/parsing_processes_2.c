/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_processes_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:12:34 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/03 17:13:52 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_parsing_token_process(char *user_input, int *from, t_data *ms)
{
	char	*tmp_t;

	tmp_t = get_token(user_input, *from);
	if (!tmp_t)
		return (ft_print_msg("get_token issue", 'm', false, ms));
	if (!deal_with_token(user_input, tmp_t, *from, ms))
		return (ft_free_return(&tmp_t, NULL, NULL, false));
	if (!ft_add_next_token_to_node(tmp_t, ms->parse_s->c))
		return (ft_free_return(&tmp_t, NULL, NULL, false));
	if (tmp_t)
		(*from) += (int) ft_strlen(tmp_t);
	return (ft_free_return(&tmp_t, NULL, NULL, true));
}

int	deal_with_token(char *str, char *tok_str, int from, t_data *ms)
{
	int		ret;

	if (from + (int) ft_strlen(tok_str) == (int) ft_strlen(str))
		return (1);
	if (!str || !tok_str || tok_str[0] == '\0' || from < 0 || \
	from >= (int) ft_strlen(str))
		return (0);
	if (!ft_is_valid_token(tok_str))
	{
		ft_print_invalid_token(ms, tok_str);
		ret = 0;
		ms->b_temoin = false;
	}
	else
		ret = 1;
	return (ret);
}

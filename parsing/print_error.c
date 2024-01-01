/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:51:09 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/01 15:02:39 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
type == s : syntax error
type == m : print message
*/
void	ft_msg_end(char *str, char type, bool del_struct, t_data *ms)
{
	if (type == 's')
		ft_printf_fd(2, "%s%s%s'\n", ms->printed_line, SYNTAX_ERR, str);
	if (type == 'm')
		ft_printf_fd(2, "minishell: error: %s\n", str);
	if (del_struct || ms)
		return ;
		/* ft_free_all(ms);*/
}

char	*ft_msg_ret_char(char *str)
{
	ft_printf_fd(2, "%s\n", str);
	return (NULL);
}

int	ft_print_msg(char *str, char type, int return_value, t_data *ms)
{
	if (type == 's')
		ft_printf_fd(2, "%s%s%s'\n", ms->printed_line, SYNTAX_ERR, str);
	if (type == 'm')
		ft_printf_fd(2, "minishell: error: %s\n", str);
	return (return_value);
}

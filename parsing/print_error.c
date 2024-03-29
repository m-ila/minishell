/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:51:09 by mbruyant          #+#    #+#             */
/*   Updated: 2024/02/02 15:28:18 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
type == s : syntax error
type == m : print message
type == q : quoting error (open quotes)
type == e : export error
should free ? or just set ms->b_temoin as 0
*/
void	ft_msg(char *str, char type, bool del_struct, t_data *ms)
{
	if (type == 's')
	{
		ft_printf_fd(2, "minishell : %s%s'\n", SYNTAX_ERR, str);
		ft_set_r_val(R_ERR_SH_B, ms);
	}
	if (type == 'm')
		ft_printf_fd(2, "minishell : error: %s\n", str);
	if (type == 'q')
		ft_printf_fd(2, "minishell : %s%c'\n", SYNTAX_ERR_Q, \
		ms->parse_s->l_reign_q);
	if (type == 'e')
	{
		ft_printf_fd(2, \
		"minishell: export: \"%s\" : not a valid identifier\n", str);
		g_return_val = R_ERR_GEN;
	}
	if (del_struct || ms)
		return ;
}

char	*ft_msg_ret_char(char *str)
{
	ft_printf_fd(2, "%s\n", str);
	return (NULL);
}

char	*ft_char_print_msg(char *str, char type, char *return_value, t_data *ms)
{
	if (type == 's')
	{
		ft_printf_fd(2, "minishell : %s%s'\n", SYNTAX_ERR, str);
		ft_set_r_val(R_ERR_SH_B, ms);
	}
	if (type == 'm')
		ft_printf_fd(2, "minishell: error: %s\n", str);
	return (return_value);
}

int	ft_print_msg(char *str, char type, int return_value, t_data *ms)
{
	if (type == 's')
	{
		ft_printf_fd(2, "minishell : %s%s'\n", SYNTAX_ERR, str);
		ft_set_r_val(R_ERR_SH_B, ms);
	}
	if (type == 'm')
		ft_printf_fd(2, "minishell: error: %s\n", str);
	if (type == 'e')
	{
		ft_printf_fd(2, \
		"minishell: export: \" %s \" : not a valid identifier\n", str);
		g_return_val = R_ERR_GEN;
	}
	if (type == 'c')
	{
		ft_printf_fd(2, "minishell: cd: %s : %s\n", str, strerror(errno));
		ft_set_r_val(R_ERR_GEN, ms);
	}
	if (type == 'C')
	{
		ft_printf_fd(2, "minishell: cd: %s", CD_ARG);
		ft_set_r_val(R_ERR_GEN, ms);
	}
	return (return_value);
}

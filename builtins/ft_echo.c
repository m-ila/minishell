/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:40:41 by chourael          #+#    #+#             */
/*   Updated: 2024/02/03 15:54:19 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_n(char c)
{
	return (c == 'n');
}

static bool	ft_valid_echo_arg_n_line(char *str)
{
	if (str[0] == '-' && ft_has_only_after(str, 1, ft_is_n))
		return (true);
	return (false);
}

int	ft_echo(t_node *c)
{
	int	i;
	int	n;
	int	len;

	if (!c)
		return (R_ERR_GEN);
	i = 0;
	n = 1;
	len = ft_2d_lines(c->ep_all_elem);
	g_return_val = R_EX_OK;
	if (len > 1)
	{
		while (c->ep_all_elem[n] && ft_valid_echo_arg_n_line(c->ep_all_elem[n]))
			n++;
		while (c->ep_all_elem[i + n])
		{
			ft_printf_fd(1, "%s", c->ep_all_elem[i + n]);
			if (i + n < len - 1)
				ft_printf_fd(1, " ");
			i++;
		}
		if (n == 1)
			ft_printf_fd(1, "\n");
	}
	return (R_EX_OK);
}

char	*ft_triple_join(char *str1, char *str2, char *str3, t_data *ms)
{
	char	*buff1;
	char	*finale;

	if (!str1 || !str2 || !str3 || !ms)
		return (ft_strdup(""));
	buff1 = ft_strjoin(str1, str2);
	if (!buff1)
		return (ft_char_print_msg("str triple join", 'm', NULL, ms));
	finale = ft_strjoin(buff1, str3);
	if (!finale)
	{
		free(buff1);
		return (ft_char_print_msg("str triple join", 'm', NULL, ms));
	}
	free(buff1);
	return (finale);
}

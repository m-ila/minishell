/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:40:41 by chourael          #+#    #+#             */
/*   Updated: 2024/01/11 10:24:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
to do : voir avec Chourael si print sur sortie standard OK si redirections
sinon changer FD dans ft_printf_fd et write
*/
int	ft_echo(t_cmd *cmds)
{
	int	i;
	int	n;

	if (!cmds)
		return (R_ERR_GEN);
	i = 1;
	n = 0;
	if (!ft_strncmp(cmds->cmd_w_arg[1], "-n", ft_strlen("-n")))
		n = 1;
	while (cmds->cmd_w_arg[i + n])
	{
		ft_printf_fd(1, "%s", cmds->cmd_w_arg[i + n]);
		i++;
	}
	if (n == 0)
		ft_printf_fd(1, "\n");
	return (R_EX_OK);
}

/*
to do : should b->temoin = false if fail ?
*/
char	*ft_triple_join(char *str1, char *str2, char *str3, t_data *ms)
{
	char	*buff1;
	char 	*finale;

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
/*
static bool		ft_skip_begg(char *str, int *i, t_cmd *cmds)
{
	if (!cmds || !str)
		return (false);
	while (str[*i] && ft_iswhitespace(str[*i]))
		(*i)++;
	if (!ft_strncmp(cmds->cmd_w_arg[0], "echo", ft_strlen("echo")))
		*i = *i + 4;
	while (str[*i] && ft_iswhitespace(str[*i]))
		(*i)++;
	if (!ft_strncmp(cmds->cmd_w_arg[1], "-n", ft_strlen("-n")))
		*i = *i + 2;
	while (str[*i] && ft_iswhitespace(str[*i]))
		(*i)++;
	if (*i == (int) ft_strlen(str))
		return (false);
	return (true);
}

char	*ft_epured_str(char *str, t_cmd *cmds)
{
	char	reigning_quote;
	char	*triple_join;
	int		nb_reigning_quotes;
	int		nb_quotes;
	int		i;

	reigning_quote = '.';
	nb_reigning_quotes = 0;
	nb_quotes = 0;
	i = 0;
	if (!ft_skip_begg(str, &i, cmds))
		return (ft_strdup(""));
	while (str[i])
	{
		if (ft_char_in_base(str[i], BASE_QUOTES))
		{
			if (str[i] != reigning_quote)
			{
				reigning_quote = str[i];
				nb_reigning_quotes++;
			}
			if (str[i] == reigning_quote)
				nb_quotes++;
		}
		if (str[i] == '$' && reigning_quote == '\'')
		{
			
		}
		i++;
	}
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:45:08 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 23:08:27 by mbruyant         ###   ########.fr       */
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

t_cmd	*ft_go_to_last_cmd_node(t_cmd *cmd_node)
{
	while (cmd_node)
	{
		if (!cmd_node->next)
			return (cmd_node);
		cmd_node = cmd_node->next;
	}
	return (NULL);
}

t_cmd	*ft_fill_cmd_struct(t_parse *ms)
{
	int		i;
	t_cmd	*struct_cmd;

	i = 0;
	struct_cmd = malloc(sizeof(*struct_cmd));
	if (!struct_cmd)
		return (NULL);
	while (ms->arr_input[i])
	{
		struct_cmd = ft_create_cmd_node(ms, i);
		i++;
	}
	return (struct_cmd);
}

int	ft_assign_tokens_values(t_cmd *ret, t_parse *ms, int i)
{
	if (i == 0)
	{
		ret->previous = NULL;

		if (ms->start_w_val_tok == 1 && ms->token_nb >= 2)
		{
			ret->prev_token = ms->arr_token[i];
			ret->next_token = ms->arr_token[i + 1];
		}
		else if (ms->start_w_val_tok == -1 && ms->token_nb >= 1)
		{
			ret->prev_token = NULL;
			ret->next_token = ms->arr_token[i];
		}
		else
		{
			ft_free_cmds(&ms->cmds);
			return (0);
		}
	}
	return (1);
}

/* creates t_cmd node from t_parse->arr_token and t_parse->arr_input
doit encore fill fd_in et fd_out en fonction de prev et next_token */
t_cmd *ft_create_cmd_node(t_parse *ms, int i)
{
	t_cmd	*ret;

	if (!ms)
		return (NULL);
	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	if (i == 0)
		ret->previous = NULL;
	if (i > 0)
	{
		ret->previous = ft_go_to_last_cmd_node(ms->cmds);
		if (!ret->previous)
		{
			ft_printf_fd(2, "prev creat_cmd_node err\n");
			ft_free_cmds(&ms->cmds);
			return (NULL);
		}
		ret->previous->next = ret;
	}
	if (!ft_assign_tokens_values(ret, ms, i))
	{
		ft_printf_fd(2, "assign token val creat_cmd_node err\n");
		ft_free_cmds(&ms->cmds);
		return (NULL);
	}
	ret->next = NULL;
	ret->cmd_w_arg = ft_split(ms->arr_input[i], ' ');
	if (!ret->cmd_w_arg)
	{
		ft_printf_fd(2, "malloc cmd_w_arg creat_cmd_node err\n");
		ft_free_cmds(&ms->cmds);
	}
	ret->cmd = ft_strdup(ret->cmd_w_arg[0]);
	if (!ret->cmd)
	{
		ft_printf_fd(2, "malloc cmd creat_cmd_node err\n");
		ft_free_cmds(&ms->cmds);
	}
	return (ret);
}

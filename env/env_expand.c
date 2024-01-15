/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:31:38 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/15 16:35:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_val_to_search_in_env(t_data *ms, t_cmd *cmds, int from)
{
	int	until;

	if (!ms->b_temoin || !cmds->epured_model || \
	from >= (int) ft_strlen(cmds->epured_model))
		return (ft_strdup(""));
	until = ft_strlen_unbase(cmds->epured_model, "1", from);
	printf("\n\n\n\ncoucou\nfrom = %d\nuntil = %d\n", from, from + until);
	return (ft_strdup_limiters(cmds->raw_str, from, from + until));
}

bool	ft_check_valid_env_var(t_data *ms, t_cmd *cmds, char *str)
{
	if (!ms->envi || !ms->b_temoin || !cmds->epured_model || \
	!str || str[0] == '\0')
		return (false);
	if (ft_tag_is_in_env(ms, str))
		return (true);
	return (false);
}

bool	ft_join_values(t_data *ms, t_cmd *cmds, int *i)
{
	char	*str1;
	char	*str3;

	ft_set_char_to_null(&str1, NULL, &str3);
	if (*i == 0)
		str1 = ft_strdup("");
	else
		str1 = ft_strdup_limiters(cmds->raw_str, 0, *i);
	if (!str1)
	{
		ms->b_temoin = false;
		return (ft_print_msg("join val str1", 'm', false, ms));
	}
	str3 = ft_strdup_limiters(cmds->raw_str, \
	*i + ft_strlen(ms->parse_struct->tmp_tag) + 1, ft_strlen(cmds->raw_str));
	if (!str3)
	{
		free(str1);
		ms->b_temoin = false;
		return (ft_print_msg("join val str3", 'm', false, ms));
	}
	free(cmds->raw_str);
	cmds->raw_str = ft_triple_join(str1, ms->parse_struct->tmp_val, str3, ms);
	ft_multiple_free(&str1, NULL, &str3);
	if (!cmds->raw_str)
	{
		ms->b_temoin = false;
		return (ft_print_msg("join val raw str", 'm', false, ms));
	}
	return (true);
}

void	ft_set_char_to_null(char **str1, char **str2, char **str3)
{
	if (str1)
		*str1 = NULL;
	if (str2)
		*str2 = NULL;
	if (str3)
		*str3 = NULL;
}

void	ft_multiple_free(char **str1, char **str2, char **str3)
{
	if (str1)
		free(*str1);
	if (str2)
		free(*str2);
	if (str3)
		free(*str3);
	ft_set_char_to_null(str1, str2, str3);
}

bool	ft_update_epur(t_data *ms, t_cmd *cmds, int *i)
{
	char	*str1;
	char	*str2;
	char	*str3;
	int		index;

	index = -1;
	ft_set_char_to_null(&str1, &str2, &str3);
	if (*i == 0)
		str1 = ft_strdup("");
	else
		str1 = ft_strdup_limiters(cmds->epured_model, 0, *i);
	if (!str1)
	{
		ms->b_temoin = false;
		return (ft_print_msg("up epur str1", 'm', false, ms));
	}
	if (ms->parse_struct->tmp_val)
		str2 = ft_calloc(ft_strlen(ms->parse_struct->tmp_val) + 1, sizeof(char));
	if (!ms->parse_struct->tmp_val)
		str2 = ft_strdup("");
	if (!str2)
	{
		free(str1);
		ms->b_temoin = false;
		return (ft_print_msg("up epur str2", 'm', false, ms));
	}
	while (++index < (int) ft_strlen(ms->parse_struct->tmp_val))
		str2[index] = '1';
	str3 = ft_strdup_limiters(cmds->epured_model, \
	*i + ft_strlen(ms->parse_struct->tmp_tag) + 1, ft_strlen(cmds->epured_model));
	if (!str3)
	{
		ft_multiple_free(&str1, &str2, NULL);
		ms->b_temoin = false;
		return (ft_print_msg("up epur str3", 'm', false, ms));
	}
	free(cmds->epured_model);
	cmds->epured_model = ft_triple_join(str1, str2, str3, ms);
	ft_multiple_free(&str1, &str2, &str3);
	if (!cmds->epured_model)
	{
		ms->b_temoin = false;
		return (ft_print_msg("update epured model", 'm', false, ms));
	}
	return (true);
}

bool	ft_do_in_env(t_data *ms, t_cmd *cmds, t_parse *ps, int *i)
{
	if (ft_tag_is_in_env(ms, ps->tmp_tag))
		ps->tmp_val = ft_get_val_in_env(ms->envi, ps->tmp_tag, ms);
	if (!ft_tag_is_in_env(ms, ps->tmp_tag))
		ps->tmp_val = ft_strdup("");
	if (!ps->tmp_val)
		return (ft_print_msg("strdup env val", 'm', false, ms));
	if (!ft_join_values(ms, cmds, i))
		return (false);
	if (!ft_update_epur(ms, cmds, i))
		return (false);
	(*i) = (*i) + ft_strlen(ps->tmp_val) - 1;
	free(ps->tmp_val);
	return (true);
}

bool	ft_var_env(t_data *ms, t_cmd *cmds)
{
	int		i;
	t_parse	*ps;

	if (!ms->b_temoin || !cmds->epured_model || !cmds->raw_str)
		return (false);
	if (!ft_strocc(cmds->epured_model, '$'))
		return (true);
	i = 0;
	ps = ms->parse_struct;
	while (i < (int) ft_strlen(cmds->raw_str))
	{
		ft_set_char_to_null(&ps->tmp_tag, &ps->tmp_val, NULL);
		if (cmds->epured_model[i] == '$')
		{
			ps->tmp_tag = ft_get_val_to_search_in_env(ms, cmds, i + 1);
			if (!ps->tmp_tag)
				return (ft_print_msg("strdup env tag", 'm', false, ms));
			if (!ft_do_in_env(ms, cmds, ps, &i))
				return (false);
			free(ps->tmp_tag);
		}
		i++;
	}
	return (true);
}

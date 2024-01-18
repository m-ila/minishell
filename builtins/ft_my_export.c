/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:27:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/18 20:55:51 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_free_return(char **str1, char **str2, char **str3, int ret)
{
	if (str1)
	{
		free(*str1);
		*str1 = NULL;
	}
	if (str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (str3)
	{
		free(*str3);
		*str3 = NULL;
	}
	return (ret);
}

void    ft_export(t_data *ms, t_cmd *cmds)
{
	int	i;
	int	len;

	if (!ms || !ms->b_temoin)
		return ;
	i = 5;
	len = (int) ft_strlen(cmds->raw_str);
	while (i < len)
	{
		while (ft_iswhitespace(cmds->raw_str[i]))
			i++;
		i++;
	}
}

/* 
divise the 
	export TAG="VALUE1 $VAR VALUE2" TAG2=VALUE3
into
	TAG="VALUE1 $VAR VALUE2" (one node)

malloc and assign p->tmp_str */
/*
bool	ft_get_value_to_assign(char *user_input, int from, t_parse *p)
{
	int		until;

	if (!user_input || from >= (int) ft_strlen(user_input))
		return (false);
	until = ft_get_index_end_of_value(user_input, from);
	p->tmp_str = ft_strdup_limiters(user_input, from, until);
	if (!p->tmp_str)
		return (ft_print_msg("get value to assign", 'm', false, NULL));
	return (true);
}
*/

/* gets the until depending on the model */
/*
int		ft_get_index_end_of_value(char *user_input, int from)
{
	int		until;
	char	*tmp_model;

	if (!user_input || from >= (int) ft_strlen(user_input))
		return (NO_INDEX_FOUND);
	until = from;
	tmp_model = ft_epured_model(user_input);
	if (!tmp_model)
		return (NO_INDEX_FOUND);
	while (tmp_model[until])
	{
		if (tmp_model[until] == '0')
		{
			if (ft_char_in_base(user_input[until], BASE_QUOTES))
			{
				until++;
				continue ;
			}
			free(tmp_model);
			return (until);
		}
		until++;
	}
	free(tmp_model);
	return (until);
}
*/
/*
si somehow pas une bonne syntaxe dans tag, return une error sur sa value
*/
/* malloc and assign p->tmp_tag */
bool	ft_exp_get_tag(char *str, int from, t_parse *p)
{
	int		len;

	if (!str || from >= (int) ft_strlen(str) || !p)
		return (false);
	p->tmp_tag = NULL;
	len = ft_strlen_base(str, "=", from);
	if (!len)
		return (false);
	p->tmp_tag = ft_strdup_limiters(str, from, from + len);
	if (!p->tmp_tag)
		return (false);
	return (true);
}

/* malloc and assign p->tmp_val if tag ain't in env */
bool	ft_exp_get_val(char *a_value, int from, t_parse *p, t_data *ms)
{
	int	len_tag;

	if (!ft_tag_is_in_env(ms, p->tmp_tag))
	{
		p->tmp_val = ft_strdup("");
		return (true);
	}
	len_tag = (int) ft_strlen(p->tmp_tag) + 1;
//	if (!ft_get_value_to_assign(a_value, from + len_tag, p))
//		return (false);
	return (true);
}

bool	ft_do_expand(t_data *ms, t_parse *p)
{
	t_cmd	*c;

	if (!ms->b_temoin || !p->tmp_str)
		return (false);
	c = p->struct_cmds;
	p->tmp_model = ft_epured_model(p->tmp_val);
	if (!p->tmp_model)
		return (ft_print_msg("do expand model", 'm', false, ms));
	if (!ft_strocc(p->tmp_model, '$'))
		return (ft_free_return(&p->tmp_model, NULL, NULL, true));
	while (ft_strocc(p->tmp_model, '$'))
		if (!ft_expand_assigned_value(p->tmp_str, p, ms))
			return (ft_free_return(&p->tmp_model, NULL, NULL, false));
	return (ft_free_return(&p->tmp_model, NULL, NULL, true));
}

bool	ft_expand_assigned_value(char *a_value, t_parse *p, t_data *ms)
{
	int		i;

	if (!ms->b_temoin || !a_value || !p->tmp_model)
		return (false);
	i = 0;
	while (p->tmp_model[i])
	{
		if (p->tmp_model[i] == '$')
		{
			if (!ft_exp_get_tag(a_value, i + 1, p))
				return (ft_print_msg("get tag exp", 'm', false, ms));
			if (!ft_exp_get_val(a_value, i + 1, p, ms))
				return (ft_print_msg("get val exp", 'm', false, ms));
			if (!ft_exp_actualise_str(a_value, i, p, ms))
				return (ft_print_msg("actualise str exp", 'm', false, ms));
			if (!ft_exp_actualise_model(a_value, i, p, ms))
				return (ft_print_msg("actualise model exp", 'm', false, ms));
			ft_free_return(&p->tmp_tag, &p->tmp_val, NULL, true);
			i = i - 1;
		}
		i++;
	}
}

/* assign str1 and str3, free a_value, assign a_value, free str1 str3*/
bool	ft_exp_actualise_str(char *a_value, int i, t_parse *p, t_data *ms)
{
	if (!ms->b_temoin || !a_value || i >= (int) ft_strlen(a_value))
		return (false);
	ft_set_char_to_null(&p->str1, &p->str2, &p->str3);
	p->str1 = ft_strdup_limiters(a_value, 0, i);
	p->str3 = ft_strdup_limiters(a_value, \
	i + 1 + (int) ft_strlen(p->tmp_tag), ft_strlen(a_value));
	if (!p->str1 || p->str3)
		return (ft_print_msg("error malloc exp act str", 'm', \
		ft_free_return(&p->str1, NULL, &p->str3, false), ms));
	free(a_value);
	a_value = ft_triple_join(p->str1, p->tmp_val, p->str3, ms);
	if (!a_value)
		return (ft_print_msg("error malloc exp act str", 'm', \
		ft_free_return(&p->str1, &p->tmp_val, &p->str3, false), ms));
	return (ft_free_return(&p->str1, NULL, &p->str3, true));
}

/*
p->str2 tmp_val ou tmp_tag ?
*/
/* assign str1 str3, free c->epured_model, assign epured model, free str1 str3 */
bool	ft_exp_actualise_model(char *a_value, int i, t_parse *p, t_data *ms)
{
	t_cmd	*c;

	if (!ms->b_temoin || !a_value || i >= (int) ft_strlen(a_value))
		return (false);
	c = p->struct_cmds;
	ft_set_char_to_null(&p->str1, &p->str2, &p->str3);
	p->str1 = ft_strdup_limiters(c->epured_model, 0, i);
	p->str3 = ft_strdup_limiters(c->epured_model, \
	i + 1 + (int) ft_strlen(p->tmp_tag), ft_strlen(c->epured_model));
	if (!p->str1 || p->str3)
		return (ft_print_msg("error malloc exp act str", 'm', \
		ft_free_return(&p->str1, NULL, &p->str3, false), ms));
	free(c->epured_model);
	c->epured_model = ft_triple_join(p->str1, p->tmp_model, p->str3, ms);
	if (!c->epured_model)
		return (ft_print_msg("error malloc exp act str", 'm', \
		ft_free_return(&p->str1, &p->tmp_model, &p->str3, false), ms));
	return (ft_free_return(&p->str1, NULL, &p->str3, true));
}

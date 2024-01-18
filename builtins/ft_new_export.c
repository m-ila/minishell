/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:27:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/19 00:23:19 by mbruyant         ###   ########.fr       */
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

int	ft_free_expand(t_parse **p, char **str1, char **str2, int ret)
{
	if ((*p)->tmp_str && !ret)
	{
		free((*p)->tmp_str);
		(*p)->tmp_str = NULL;
	}
	if ((*p)->model1 && !ret)
	{
		free((*p)->model1);
		(*p)->model1 = NULL;
	}
	if ((*p)->model2 && !ret)
	{
		free((*p)->model2);
		(*p)->model2 = NULL;
	}
	if ((*p)->model3 && !ret)
	{
		free((*p)->model3);
		(*p)->model3 = NULL;
	}
	ft_free_return(&(*p)->str1, &(*p)->str2, &(*p)->str3, ret);
	ft_free_return(&(*p)->tmp_tag, &(*p)->tmp_model, &(*p)->tmp_val, ret);
	return (ft_free_return(str1, str2, NULL, ret));
}

bool	ft_translate_tag_to_val(t_parse *p)
{
	int		doll_ind;
	int		len_sum;

	doll_ind = ft_strindex(p->tmp_model, '$');
	if (doll_ind == -1)
		return (true);
	/* left */
	p->str1 = ft_strdup_limiters(p->tmp_str, 0, doll_ind);
	p->model1 = ft_strdup_limiters(p->tmp_model, 0, doll_ind);
	/* tag before processing */
	p->str2 = ft_strdup_limiters(p->tmp_str, doll_ind + 1, \
	doll_ind + 1 + ft_strlen_base(p->tmp_model, "0sS$", doll_ind + 1));
	len_sum = (int) ft_strlen(p->str1) + (int) ft_strlen(p->str2) + 1;
	/* right */
	p->str3 = ft_strdup_limiters(p->tmp_str, len_sum, (int) ft_strlen(p->tmp_str));
	p->model3 = ft_strdup_limiters(p->tmp_model, len_sum, (int) ft_strlen(p->tmp_str));
	if (!p->str1 || !p->str2 || !p->str3 || !p->model1 || !p->model3)
		return (ft_free_expand(&p, NULL, NULL, false));
	return (true);
}

bool	ft_translate_vars(char **str, t_data *ms)
{
	t_parse	*p;
	char	*model_quotes;

	if (!str || !ms->b_temoin || !ms->parse_struct)
		return (false);
	p = ms->parse_struct;
	p->tmp_model = ft_epured_model(*str, ft_cut_only_quotes);
	p->tmp_str = ft_strdup(*str);
	if (!p->tmp_model || !p->tmp_str)
		return (false);
	if (!ft_strocc_base(p->tmp_model, "$0qQ"))
		return (ft_free_return(&p->tmp_model, &p->tmp_str, NULL, true));
	while (ft_strocc_base(p->tmp_model, "$"))
	{
		if (!ft_translate_tag_to_val(p))
			return (false);
		model_quotes = ft_epured_model(p->str2, ft_cut_only_quotes);
		p->tmp_tag = ft_epured_str(p->str2, model_quotes);
		ft_multiple_free(&p->str2, NULL, NULL);
		p->model2 = ft_epured_model(p->tmp_tag, ft_cut_only_quotes);
		if (ft_tag_is_in_env(ms, p->tmp_tag))
			p->tmp_val = ft_get_val_in_env(ms->envi, p->tmp_tag, ms);
		else
			p->tmp_val = ft_strdup("");
		if (!p->tmp_val)
			return (ft_free_expand(&p, &model_quotes, NULL, false));
		free(p->tmp_str);
		p->tmp_str = ft_triple_join(p->str1, p->tmp_val, p->str3, ms);
		ft_free_expand(&p, &model_quotes, &p->tmp_model, true);
		ft_multiple_free(&p->model1, &p->model2, &p->model3);
		p->tmp_model = ft_epured_model(p->tmp_str, ft_cut_only_quotes);
		if (!p->tmp_model)
			return (ft_free_return(&p->tmp_model, NULL, NULL, false));
	}
	free(p->tmp_model);
	p->tmp_model = ft_epured_model(p->tmp_str, ft_cut_only_quotes);
	free(*str);
	if (ft_strocc_base(p->tmp_model, "0"))
	{
		*str = ft_epured_str(p->tmp_str, p->tmp_model);
		free(p->tmp_str);
		p->tmp_str = ft_strdup(*str);
		free(*str);
	}
	free(p->tmp_model);
	ft_free_return(&p->model1, &p->model2, &p->model3, true);
	*str = p->tmp_str;
	return (true);
}

bool	ft_local_str(char *str, t_data *ms, t_cmd *c)
{
	char	*loc_tag;
	char	*loc_val;
	int		until;

	if (!c || !ms)
		return (false);
	ft_set_char_to_null(&loc_tag, &loc_val, NULL);
	until = ft_export_first_eq(str);
	loc_tag = ft_strdup_limiters(str, 0, until);
	loc_val = ft_strdup_limiters(str, until + 1, (int) ft_strlen(str));
	if (!loc_tag || !loc_val)
		return (ft_free_return(&loc_tag, &loc_val, NULL, false));
	ft_printf_fd(1, "tag : (d)%s(f)\nval : (d)%s(f)\n", loc_tag, loc_val);
	ft_translate_vars(&loc_tag, ms);
	ft_translate_vars(&loc_val, ms);
	if (!loc_tag || !loc_val)
		return (ft_free_return(&loc_tag, &loc_val, NULL, false));
	ft_printf_fd(1, "translated tag : (d)%s(f)\ntranslated val : (d)%s(f)\n\n", loc_tag, loc_val);
	return (ft_free_return(&loc_tag, &loc_val, NULL, true));
}

bool	ft_export_has_eq(char *str)
{
	size_t	i;
	size_t	occ;

	if (!str)
		return (false);
	i = 0;
	occ = 0;
	while (str[i])
	{
		if (str[i] == '=' && !ft_elem_is_in_quotes(str, i))
			occ++;
		i++;
	}
	if (!occ)
		return (false);
	return (true);
}

int	ft_export_first_eq(char *str)
{
	size_t	i;

	if (!str)
		return (NO_INDEX_FOUND);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && !ft_elem_is_in_quotes(str, i))
			return (i);
		i++;
	}
	return (NO_INDEX_FOUND);
}

bool	ft_export_valid_entry(char *str)
{
	if (!str)
		return (false);
	if (!ft_export_has_eq(str) || ft_export_first_eq(str) == -1)
		return (false);
	return (true);
}

int    ft_export(t_data *ms, t_cmd *cmds)
{
	char	*export_model;
	char	*cleaned_str;
	char	**export_split;
	int		i;
//	t_parse	*p;

	if (!cmds)
		return (R_ERR_GEN);
	export_model = ft_epured_model(ms->user_input, ft_export_cond_cut);
	cleaned_str = ft_epured_str(ms->user_input, export_model);
	export_split = ft_split_epured(ms->user_input, export_model, '0');
	i = 1;
//	p = ms->parse_struct;
	ft_printf_fd(1, "export model : (d)%s(f)\ncleaned str : (d)%s(f)\n", \
	export_model, cleaned_str);
	while (export_split[i])
	{
		ft_printf_fd(1, "split[%d] : (d)%s(f)\n", i, export_split[i]);
		if (ft_export_valid_entry(export_split[i]))
			if (!ft_local_str(export_split[i], ms, cmds))
				break ;
		i++;
	}
	ft_multiple_free(&export_model, &cleaned_str, NULL);
	ft_free_2d_array(export_split);
	return (R_EX_OK);
}

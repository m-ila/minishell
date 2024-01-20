/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:27:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/20 17:03:06 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

bool	ft_exp_in_env(char *t, char *v, t_data *ms)
{
	if (ft_tag_is_in_env(ms, t))
		if (!ft_actualise_env(ms, t, v))
			return (false);
	if (!ft_tag_is_in_env(ms, t))
		if (!ft_add_in_env(ms, t, v))
			return (false);
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
	if (ft_export_valid_entry(NULL, &loc_tag, &loc_val, 2))
		if (!ft_exp_in_env(loc_tag, loc_val, ms))
			ft_msg("export : add to env fail", 'm', false, ms);
	return (ft_free_return(&loc_tag, &loc_val, NULL, true));
}

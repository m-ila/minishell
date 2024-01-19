/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:33:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/19 12:13:33 by mbruyant         ###   ########.fr       */
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

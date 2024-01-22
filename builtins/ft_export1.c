/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:33:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 20:52:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_translate_tag_to_val(t_parse *p)
{
	int		doll_ind;
	int		len_sum;

	doll_ind = ft_strindex(p->tmp_model, '$');
	if (doll_ind == -1)
		return (true);
	p->str1 = ft_strdup_limiters(p->tmp_str, 0, doll_ind);
	p->model1 = ft_strdup_limiters(p->tmp_model, 0, doll_ind);
	p->str2 = ft_strdup_limiters(p->tmp_str, doll_ind + 1, \
	doll_ind + 1 + ft_strlen_base(p->tmp_model, "0sS$X", doll_ind + 1));
	len_sum = (int) ft_strlen(p->str1) + (int) ft_strlen(p->str2) + 1;
	p->str3 = ft_strdup_limiters(p->tmp_str, len_sum, \
	(int) ft_strlen(p->tmp_str));
	p->model3 = ft_strdup_limiters(p->tmp_model, len_sum, \
	(int) ft_strlen(p->tmp_str));
	if (!p->str1 || !p->str2 || !p->str3 || !p->model1 || !p->model3)
		return (ft_free_expand(&p, NULL, NULL, false));
	return (true);
}

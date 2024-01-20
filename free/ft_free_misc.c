/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:20:39 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/20 18:22:07 by mbruyant         ###   ########.fr       */
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

int	ft_free_ret_2(char **str1, char **str2, char ***two_dim, int ret_v)
{
	ft_multiple_free(str1, str2, NULL);
	ft_free_2d_array(*two_dim);
	return (ret_v);
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

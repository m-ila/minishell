/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:31:20 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/22 15:31:39 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:38:57 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 19:43:28 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* return how many single char in str is in a base */
int	ft_strocc_base(char *str, char *base)
{
	int	i;
	int	occ;

	if (!str || !*str || !base || !*base)
		return (0);
	i = 0;
	occ = 0;
	while (str[i])
	{
		if (ft_char_in_base(str[i], base))
			occ++;
		i++;
	}
	return (occ);
}

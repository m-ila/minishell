/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:15:41 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/26 23:18:20 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_is_valid_token(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 2 || len == 0)
		return (false);
	if (len == 1)
		return (ft_char_in_base(*str, BASE_TOKEN));
	if (str[0] != str[1] || !ft_strbase(str, BASE_TOKEN))
		return (false);
	return (true);
}

static int	ft_case_by_case(char *buff)
{
	int	ret;

	if (ft_strlen(buff) == 1)
	{
		if (!ft_strncmp(buff, "|", ft_strlen(buff)))
			ret = 0;
		if (!ft_strncmp(buff, "<", ft_strlen(buff)))
			ret = 1;
		if (!ft_strncmp(buff, ">", ft_strlen(buff)))
			ret = 1;
	}
	else if (ft_strlen(buff) == 2)
	{
		if (!ft_strncmp(buff, "<<", ft_strlen(buff)))
			ret = 1;
		if (!ft_strncmp(buff, ">>", ft_strlen(buff)))
			ret = 1;
	}
	else
		ret = 0;
	if (ret == 0)
		ft_msg_end(buff, 's', false, NULL);
	free(buff);
	return (ret);
}

/* dans le parsing, si !ft_starts_w_valid_token, juste free the prompt struct
msg erreur deja dans la fonction 
renvoie -1 si aucun token dans str
if i == end, means it doesn't start by a token, returns -1 */
int	ft_starts_with_valid_token(char *str)
{
	int		i;
	int		end;
	char	*buff;

	i = 0;
	if (!ft_strocc_base(str, BASE_TOKEN))
		return (-1);
	while (str[i] && ft_char_in_base(str[i], BASE_WHITESP))
		i++;
	end = i;
	while (str[end] && ft_char_in_base(str[end], BASE_TOKEN))
		end++;
	if (i == end)
		return (-1);
	buff = ft_strdup_limiters(str, i, end);
	if (!buff)
		return (0);
	return (ft_case_by_case(buff));
}

/* if all are valids, return nb of it, if not returns 0
Si aucun token, entree valide, renvoie -1
NOTE : DOIT AFFICHER MESSAGE D'ERREUR ICI */
int	ft_get_valid_token_nb(char **token_arr, char *str)
{
	int	i;
	int	nb;

	if (!token_arr || !ft_starts_with_valid_token(str))
		return (0);
	if (!ft_strlen(*token_arr))
		return (-1);
	i = 0;
	nb = 0;
	while (token_arr[i])
	{
		if (!ft_is_valid_token(token_arr[i]))
		{
			ft_msg_end(token_arr[i], 's', false, NULL);
			return (0);
		}
		if (ft_is_valid_token(token_arr[i]))
			nb++;
		i++;
	}
	return (nb);
}

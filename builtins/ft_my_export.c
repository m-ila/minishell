/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:27:04 by mbruyant          #+#    #+#             */
/*   Updated: 2024/01/16 15:31:07 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
si somehow pas une bonne syntaxe dans tag, return une error sur sa value
*/
char	ft_get_tag(char *str, int from)
{
	char	*ret_tag;
	int		len;

	if (!str || from >= (int) ft_strlen(str))
		return (NULL);
	ret_tag = NULL;
	len = ft_strlen_base(str, "=", from);
	if (!len)
		return (NULL);
	ret_tag = ft_strdup_limiters(str, from, from + len);
	return (ret_tag);
}

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

bool	ft_do_expand(t_data *ms, char *a_value)
{
	char	*model;

	if (!ms->b_temoin || !a_value)
		return (false);
	model = ft_epured_model(a_value);
	if (!model)
		return (ft_print_msg("do expand model", 'm', false, ms));
	if (!ft_strocc(a_value, '$'))
	{
		free(model);
		return (true);
	}
	
}

char	*ft_expand_assigned_value(char *user_input, char *model)
{

}

char	*ft_get_value_to_assign(char *user_input, int from)
{
	char	*to_assign;
	int		until;

	if (!user_input || from >= (int) ft_strlen(user_input))
		return (NULL);
	until = ft_get_index_end_of_value(user_input, from);
	to_assign = ft_strdup_limiters(user_input, from, until);
	return (to_assign);
}

char	ft_get_variable(char *str)

bool    ft_is_valid_tag(char *str)
{
	
}

void    ft_export(t_data *ms, t_cmd *cmds)
{
	if (!ms || !ms->b_temoin)
		return ;
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:51:46 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/23 21:50:40 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_node	*ft_find_prev_node(t_env_node **envi, char *tag_)
{
	t_env_node	*ret;

	if (!envi || *envi == NULL)
		return (NULL);
	ret = *envi;
	while (ret->next)
	{
		if (!ft_strncmp(ret->next->n_tag, tag_, ft_strlen(ret->next->n_tag)))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_env_node	*ft_find_node(t_env_node **envi, char *tag_)
{
	t_env_node	*ret;

	if (!envi || *envi == NULL)
		return (NULL);
	ret = *envi;
	while (ret)
	{
		if (!ft_strncmp(ret->n_tag, tag_, ft_strlen(ret->n_tag)))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

/* comment : need to add if !envi->next : mettre a NULL NULL ? */
static void	ft_do_del_first(t_env_node **envi, char *tag_)
{
	t_env_node	*buff;

	if (!envi || !(*envi))
		return ;
	if (ft_strncmp((*envi)->n_tag, tag_, ft_strlen((*envi)->n_tag)))
		return ;
	if ((*envi)->next)
	{
		buff = *envi;
		*envi = (*envi)->next;
		ft_free_node(buff);
		return ;
	}
	else
	{
		ft_free_node(*envi);
		*envi = ft_create_node(NULL, "", "");
		return ;
	}
}

/* check if : not finding, only 1 node (check if leak looking for it) */
void	ft_env_del_elem(t_env_node **envi, char *tag_)
{
	t_env_node	*prev;
	t_env_node	*curr;

	if (!envi || !(*envi))
		return ;
	prev = ft_find_prev_node(envi, tag_);
	if (!prev)
		return (ft_do_del_first(envi, tag_));
	curr = prev->next;
	if (!curr->next)
	{
		prev->next = NULL;
		ft_free_node(curr);
	}
	else
	{
		prev->next = curr->next;
		ft_free_node(curr);
	}
}

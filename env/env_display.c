/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:15:03 by mbruyant          #+#    #+#             */
/*   Updated: 2023/12/23 21:24:09 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* TESTED : WORKS don't seem to leak
si !cont on strdup "" pour eviter leak */
void	ft_env_update(t_env_node *envi, char *tag_, char *cont)
{
	if (!envi || !tag_)
		return ;
	if (!cont)
	{
		cont = ft_strdup("");
		if (!cont)
			return ;
	}
	if (!ft_exists_in_env(envi, tag_))
		return ;
	while (envi)
	{
		if (!ft_strncmp(envi->n_tag, tag_, ft_strlen(envi->n_tag)))
		{
			free(envi->n_content);
			envi->n_content = ft_strdup(cont);
			if (!envi->n_content)
			{
				printf("Update envi node failed !\n");
				ft_env_free(envi);
			}
			break ;
		}
		envi = envi->next;
	}
}

/* tested : OK 
attention : quand on l'appelle genre dans main il faut bien mettre la condition
si env existe !! sinon leak, car ici ne deal qu'avec node et pas env struct */
void	ft_env_display(t_env_node **envi)
{
	t_env_node	*curr;

	if (!envi || !*envi)
		return ;
	curr = *envi;
	while (curr)
	{
		if (curr->n_tag[0] != '\0' || curr->n_content[0] != '\0')
			printf("%s=%s\n", curr->n_tag, curr->n_content);
		curr = curr->next;
	}
}

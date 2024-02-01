/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:45:23 by chchour           #+#    #+#             */
/*   Updated: 2024/02/01 21:14:37 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*makerendu(char *buffer, char *rendu, int remember, int back)
{
	int	i;
	int	o;

	i = 0;
	o = back;
	rendu = malloc(sizeof(char) * (remember + 1));
	while (i < remember - back)
	{
		rendu[i] = buffer[o];
		i++;
		o++;
	}
	rendu[i] = '\0';
	return (rendu);
}

void	feedsnake(t_gnl *d, int j)
{
	int	i;

	i = 0;
	if (j == 1)
	{
		while (i < d->memo)
		{
		d->snake[i] = d->snake2[i];
		i++;
		}
		d->snake[i] = '\0';
	}
	else if (j == 2)
	{
		while (i < d->memo)
		{
		d->snake2[i] = d->snake[i];
		i++;
		}
		d->snake2[i] = '\0';
	}
}

int	ft_init(t_gnl *d)
{
	d->snake = NULL;
	d->snake2 = NULL;
	d->rendusize = 0;
	d->memo = 0;
	return (0);
}

void	ft_reinit(t_gnl *d, int remember)
{
	d->snake = NULL;
	d->snake2 = NULL;
	d->memo = 0;
	d->rendusize = d->readsize - remember;
}

char	*resnake(t_gnl *d, int i)
{
	if (i == 1)
	{
		d->snake[d->memo] = '\0';
		return (d->snake);
	}
	else if (i == 2)
	{
		d->snake2[d->memo] = '\0';
		return (d->snake2);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:45:13 by chchour           #+#    #+#             */
/*   Updated: 2024/02/01 21:14:34 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ouoroboros2(char *buffer, t_gnl *d, int fd)
{
	d->snake = malloc(sizeof(char) * (d->rendusize + d->readsize + 1));
	if (d->snake == NULL)
		return (-1);
	if (d->snake2)
	{
		feedsnake(d, 1);
		free (d->snake2);
		d->snake2 = NULL;
		d->readsize = read(fd, buffer, BUFFER_SIZE);
		if (d->readsize == -1)
			return (-1);
		buffer[d->readsize] = '\0';
		d->rendusize = d->rendusize + d->readsize;
	}
	return (0);
}

static int	ouroboros3(char *buffer, t_gnl *d, int *remember, int fd)
{
	*remember = 0;
	d->readsize = read(fd, buffer, BUFFER_SIZE);
	if (d->readsize == -1)
		return (-1);
	buffer[d->readsize] = '\0';
	d->rendusize += d->readsize;
	d->snake2 = malloc(sizeof(char) * (d->rendusize + 1));
	if (d->snake2 == NULL)
		return (-1);
	feedsnake(d, 2);
	free(d->snake);
	d->snake = NULL;
	return (0);
}

char	*ouroboros(char *buffer, t_gnl *d, int *remember, int fd)
{
	while (d->readsize > 0)
	{
		if (ouoroboros2(buffer, d, fd) == -1)
			return (NULL);
		while (d->memo < d->rendusize)
		{
			d->snake[d->memo++] = buffer[(*remember)++];
			if (d->snake[d->memo - 1] == '\n')
				return (resnake(d, 1));
		}
		if (ouroboros3(buffer, d, remember, fd) == -1)
			return (NULL);
		while (*remember < d->readsize)
		{
			d->snake2[d->memo++] = buffer[(*remember)++];
			if (d->snake2[d->memo - 1] == '\n')
				return (resnake(d, 2));
		}
		*remember = 0;
	}
	free(buffer);
	if (d->snake == NULL)
		return (d->snake2);
	else
		return (d->snake);
}

char	*rendu_in_preparation(char *buffer, char *rendu, t_gnl *d, int fd)
{
	static int		remember = 0;
	int				back;
	char			*line;

	back = remember;
	while (remember < d->readsize)
	{
		if (buffer[remember] == '\n')
		{
			(remember)++;
			return (makerendu(buffer, rendu, remember, back));
		}
		remember++;
	}
	remember = back;
	ft_reinit(d, remember);
	line = ouroboros(buffer, d, &remember, fd);
	if (!line)
		return (NULL);
	if (line[0] == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*rendu = NULL;
	static char		*buffer = NULL;
	static t_gnl	d;

	if (ft_init(&d) == -1 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return (NULL);
		d.readsize = read(fd, buffer, BUFFER_SIZE);
		if (d.readsize == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[d.readsize] = '\0';
		if (d.readsize == 0)
			free(buffer);
	}
	if (d.readsize == 0)
		return (NULL);
	return (rendu_in_preparation(buffer, rendu, &d, fd));
}

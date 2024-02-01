/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:23:32 by mbruyant          #+#    #+#             */
/*   Updated: 2023/06/24 23:51:12 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_null(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
}

static char	*ft_read(int fd, char *buffer, char *temp)
{
	int		index;
	char	*str_temp;

	index = 1;
	while (index)
	{
		index = read(fd, buffer, BUFFER_SIZE);
		if (index == -1)
			return (NULL);
		if (index == 0)
			break ;
		buffer[index] = '\0';
		if (!temp)
			temp = ft_strdup("");
		str_temp = temp;
		temp = ft_strjoin(str_temp, buffer);
		ft_null(&str_temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (temp);
}

static char	*ft_line(char *line)
{
	size_t	len;
	char	*temp;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	if (line[len] == '\0' || line[1] == '\0')
		return (NULL);
	temp = ft_substr(line, len + 1, ft_strlen(line) - len);
	if (temp[0] == 0)
		ft_null(&temp);
	line[len + 1] = '\0';
	return (temp);
}

char	*get_next_line(int fd)
{
	static char		*temp;
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	line = ft_read(fd, buffer, temp);
	ft_null(&buffer);
	if (!line)
		return (NULL);
	temp = ft_line(line);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:00:55 by mbouaza           #+#    #+#             */
/*   Updated: 2023/01/19 03:31:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include */

#include "get_next_line_bonus.h"
#include <stdlib.h>

/* str_without_newline */

char	*str_without_newline(int fd, char *storage)
{
	char	buf[BUFFER_SIZE + 1];
	int		size;

	size = 1;
	while (!check_newline('\n', storage) && size != 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
		{
			free(storage);
			return (NULL);
		}
		buf[size] = '\0';
		storage = ft_strjoin(storage, buf);
	}
	return (storage);
}

/* str_with_newline */

char	*str_with_newline(char *storage)
{
	int		i;
	char	*line;

	if (!storage[0])
		return (NULL);
	line = malloc(sizeof(char) * ft_strlen(storage) + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/* get_rest_add_storage */

// Whene get_next_line return a line, my static is free add the rest //
// after "\n" in this static //

static char	*get_rest_add_storage(char *storage)
{
	char	*new_storage;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (storage[i] != '\n' && storage[i])
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = malloc(sizeof(char) * ft_strlen(storage) - i + 1);
	if (!new_storage)
		return (NULL);
	i++;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

/* get_next_line / bonus */

char	*get_next_line(int fd)
{
	static char	*storage[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage[fd] = str_without_newline(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = str_with_newline(storage[fd]);
	storage[fd] = get_rest_add_storage(storage[fd]);
	if (!storage[fd])
		free(storage[fd]);
	return (line);
}

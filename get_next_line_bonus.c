/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboustan <jboustan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 23:44:55 by jboustan          #+#    #+#             */
/*   Updated: 2024/07/06 23:28:34 by jboustan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char **saved_buffer)
{
	char	*line;
	char	*newline_position;
	size_t	line_length;
	size_t	index;

	newline_position = ft_strchr(*saved_buffer, '\n');
	line_length = 0;
	if (newline_position)
		line_length = newline_position - *saved_buffer + 1;
	else
		line_length = ft_strlen(*saved_buffer);
	line = (char *)malloc(line_length + 1);
	if (!line)
		return (NULL);
	index = 0;
	while ((*saved_buffer)[index] && (*saved_buffer)[index] != '\n')
	{
		line[index] = (*saved_buffer)[index];
		index++;
	}
	if ((*saved_buffer)[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

static void	update_saved_buffer(char **saved_buffer)
{
	char	*newline_position;
	char	*new_saved_buffer;

	newline_position = ft_strchr(*saved_buffer, '\n');
	if (newline_position)
	{
		new_saved_buffer = ft_strdup(newline_position + 1);
		free(*saved_buffer);
		*saved_buffer = new_saved_buffer;
	}
	else
	{
		free(*saved_buffer);
		*saved_buffer = NULL;
	}
}

static char	*append_to_buffer(char *saved_buffer, char *read_buffer)
{
	char	*temp_buffer;

	if (saved_buffer)
	{
		temp_buffer = ft_strjoin(saved_buffer, read_buffer);
		free(saved_buffer);
		saved_buffer = temp_buffer;
	}
	else
	{
		saved_buffer = ft_strdup(read_buffer);
	}
	return (saved_buffer);
}

static char	*read_and_append(int file_descriptor, char *saved_buffer)
{
	char	*read_buffer;
	ssize_t	bytes_read;

	read_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	bytes_read = read(file_descriptor, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		saved_buffer = append_to_buffer(saved_buffer, read_buffer);
		if (ft_strchr(read_buffer, '\n'))
			break ;
		bytes_read = read(file_descriptor, read_buffer, BUFFER_SIZE);
	}
	free(read_buffer);
	if (bytes_read < 0)
	{
		free(saved_buffer);
		return (NULL);
	}
	return (saved_buffer);
}

char	*get_next_line(int fd)
{
	static char	*saved_buffers[MAX_FD] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	saved_buffers[fd] = read_and_append(fd, saved_buffers[fd]);
	if (!saved_buffers[fd])
		return (NULL);
	if (!*saved_buffers[fd])
	{
		free(saved_buffers[fd]);
		saved_buffers[fd] = NULL;
		return (NULL);
	}
	line = extract_line(&saved_buffers[fd]);
	update_saved_buffer(&saved_buffers[fd]);
	return (line);
}

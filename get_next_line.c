/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboustan <jboustan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:26:51 by jboustan          #+#    #+#             */
/*   Updated: 2024/07/06 22:50:35 by jboustan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **saved_buffer)
{
	char	*line;
	char	*newline_position;
	size_t	line_length;
	size_t	i;

	newline_position = ft_strchr(*saved_buffer, '\n');
	line_length = 0;
	i = 0;
	if (newline_position)
		line_length = newline_position - *saved_buffer + 1;
	else
		line_length = ft_strlen(*saved_buffer);
	line = (char *)malloc(line_length + 1);
	if (!line)
		return (NULL);
	while ((*saved_buffer)[i] && (*saved_buffer)[i] != '\n')
	{
		line[i] = (*saved_buffer)[i];
		i++;
	}
	if ((*saved_buffer)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static void	update_save(char **saved_buffer)
{
	char	*newline_position;
	char	*temp_buffer;

	newline_position = ft_strchr(*saved_buffer, '\n');
	if (newline_position)
	{
		temp_buffer = ft_strdup(newline_position + 1);
		free(*saved_buffer);
		*saved_buffer = temp_buffer;
	}
	else
	{
		free(*saved_buffer);
		*saved_buffer = NULL;
	}
}

static char	*append_buffer(char *saved_buffer, char *read_buffer)
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

static char	*read_and_append(int fd, char *saved_buffer)
{
	ssize_t		bytes_read;
	char		*read_buffer;

	read_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		saved_buffer = append_buffer(saved_buffer, read_buffer);
		if (ft_strchr(read_buffer, '\n'))
			break ;
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
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
	static char	*saved_buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved_buffer = read_and_append(fd, saved_buffer);
	if (!saved_buffer)
		return (NULL);
	if (!*saved_buffer)
	{
		free(saved_buffer);
		saved_buffer = NULL;
		return (NULL);
	}
	line = extract_line(&saved_buffer);
	update_save(&saved_buffer);
	return (line);
}

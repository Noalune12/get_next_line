/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:46:32 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/26 11:37:17 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
	return (NULL);
}

static char	*update_buffer(char *buffer)
{
	char	*next_line;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free(buffer));
	next_line = ft_calloc(ft_strlen(buffer) - i, sizeof(char));
	if (!next_line)
		return (NULL);
	j = 0;
	while (buffer[++i])
	{
		next_line[j] = buffer[i];
		j++;
	}
	ft_free(buffer);
	return (next_line);
}

static char	*get_line(char *content)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!content[i])
		return (NULL);
	while (content[i] && content[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '\n')
	{
		line[i] = content[i];
		i++;
	}
	if (content[i] && content[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*read_file(int fd, char *remaining_content, char *buffer)
{
	ssize_t	b_read;
	char	*temp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
			return (ft_free(remaining_content));
		else if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		temp = ft_strjoin(remaining_content, buffer);
		ft_free(remaining_content);
		if (!temp)
			return (NULL);
		remaining_content = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remaining_content);
}

char	*get_next_line(int fd)
{
	static char	*remaining_content;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (remaining_content)
		{
			free(remaining_content);
			remaining_content = NULL;
		}
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(remaining_content));
	remaining_content = read_file(fd, remaining_content, buffer);
	free(buffer);
	if (!remaining_content)
		return (NULL);
	line = get_line(remaining_content);
	remaining_content = update_buffer(remaining_content);
	return (line);
}

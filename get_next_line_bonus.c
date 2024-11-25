/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:46:32 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/25 18:37:44 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
// update buffer

// update buffer

static char	*update_buffer(char *buffer)
{
	char	*next_line;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next_line = ft_calloc(ft_strlen(buffer) - i, sizeof(char));
	if (!next_line)
		return (NULL);
	j = 0;
	while (buffer[++i])
	{
		next_line[j] = buffer[i];
		j++;
	}
	free(buffer);
	return (next_line);
}

// extract exactly one line

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

// read file until \n with BUFFER_SIZE
static char	*content_join(char *content, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(content, buffer);
	if (content)
		free(content);
	if (!temp)
		return (NULL);
	return (temp);
}

static char	*read_file(int fd, char *remaining_content, char *buffer)
{
	int		b_read;
	char	*temp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
			return (free(remaining_content), NULL);
		else if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!remaining_content)
			remaining_content = ft_strdup("");
		temp = content_join(remaining_content, buffer);
		if (!temp)
			return (free(remaining_content), NULL);
		remaining_content = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remaining_content);
}

char	*get_next_line(int fd)
{
	static char	*remaining_content[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (remaining_content[fd])
		{
			free(remaining_content[fd]);
			remaining_content[fd] = NULL;
		}
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	remaining_content[fd] = read_file(fd, remaining_content[fd], buffer);
	free(buffer);
	if (!remaining_content[fd])
		return (NULL);
	line = get_line(remaining_content[fd]);
	remaining_content[fd] = update_buffer(remaining_content[fd]);
	return (line);
}

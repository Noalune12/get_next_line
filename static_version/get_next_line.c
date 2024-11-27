/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:46:32 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/27 13:40:54 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_buffer(char *buffer)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen_c(buffer, '\0');
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		ft_memset(buffer, '\0', len);
		return (NULL);
	}
	ft_memmove(buffer, buffer + i + 1, len - i);
	ft_memset(buffer + len - i, '\0', i + 1);
	return (buffer);
}

static int	copy_line(char *line, char *content,
	char *line_extracted, size_t *index)
{
	size_t	i;

	i = 0;
	while (content[i] && content[i] != '\n')
	{
		line_extracted[*index] = content[i];
		i++;
		(*index)++;
	}
	if (content[i] && content[i] == '\n')
	{
		line_extracted[*index] = '\n';
		line_extracted[*index + 1] = '\0';
		free(line);
		return (1);
	}
	return (0);
}

static char	*join_line_content(char *line, char *content)
{
	size_t	i;
	size_t	line_len;
	char	*line_extracted;

	if (!line)
		line_len = 0;
	else
		line_len = ft_strlen_c(line, '\n');
	line_extracted = (char *)malloc((line_len
				+ ft_strlen_c(content, '\n') + 1) * sizeof(char));
	if (!line_extracted)
		return (NULL);
	i = 0;
	if (line_len > 0)
	{
		if (copy_line(line, line, line_extracted, &i) == 1)
			return (line_extracted);
	}
	if (copy_line(line, content, line_extracted, &i) == 1)
		return (line_extracted);
	line_extracted[i] = '\0';
	free(line);
	return (line_extracted);
}

static char	*read_file_and_extract_line(int fd, char *content, char *line)
{
	ssize_t	b_read;
	char	*temp;

	b_read = 1;
	while (b_read > 0 && !(ft_strchr(content, '\n')))
	{
		b_read = read(fd, content, BUFFER_SIZE);
		if (b_read < 0)
		{
			ft_memset(content, '\0', BUFFER_SIZE + 1);
			return (ft_free(line));
		}
		else if (b_read == 0)
			break ;
		content[b_read] = '\0';
		temp = join_line_content(line, content);
		if (!temp)
			return (ft_free(line));
		line = temp;
		if (ft_strchr(content, '\n'))
			break ;
		ft_memset(content, '\0', BUFFER_SIZE + 1);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	content[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (content[0])
		line = join_line_content(line, content);
	line = read_file_and_extract_line(fd, content, line);
	if (!line)
	{
		ft_memset(content, '\0', BUFFER_SIZE + 1);
		return (NULL);
	}
	update_buffer(content);
	return (line);
}

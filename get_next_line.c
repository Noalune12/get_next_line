/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:46:32 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/25 18:37:26 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*remaining_content;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
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
		return (NULL);
	remaining_content = read_file(fd, remaining_content, buffer);
	free(buffer);
	if (!remaining_content)
		return (NULL);
	line = get_line(remaining_content);
	remaining_content = update_buffer(remaining_content);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (1);

// 	int		fd;
// 	char	*line;

// 	// //read only one line
// 	// printf("READ FILE UNTIL 1st \\n\n\n");
// 	// fd = open(argv[1], O_RDONLY);
// 	// line = read_file(fd);
// 	// printf("LINE = %s", line);
// 	// free(line);
// 	// close(fd);

// 	// //get line
// 	// printf("\n\nGET 1ST LINE\n\n");
// 	// char *content;
// 	// fd = open(argv[1], O_RDONLY);
// 	// content = read_file(fd);
// 	// printf("CONTENT = %s\n", content);
// 	// line = get_line(content);
// 	// printf("LINE = '%s'", line);
// 	// free(content);
// 	// free(line);
// 	// close(fd);

// 	// //get linesfd
// 	// printf("\n\nGET LINES\n\n");
// 	// fd = open(argv[1], O_RDONLY);
// 	// while (1)
// 	// {
// 	// 	content = read_file(fd);
// 	// 	if (!content)
// 	// 		break ;
// 	// 	printf("CONTENT = %s\n", content);
// 	// 	line = get_line(content);
// 	// 	if (!line)
// 	// 		break ;
// 	// 	printf("LINE = '%s'", line);
// 	// 	content = update_buffer(content);
// 	// 	printf("\nCONTENT = %s\n\n", content);
// 	// 	free(line);
// 	// 	free(content);
// 	// }

// 	// free(content);
// 	// free(line);
// 	// close(fd);

// 	//get next line
// 	printf("\n\nGET NEXT LINE\n\n");
// 	fd = open(argv[1], O_RDONLY);
// 	printf("fd = %d\n\n", fd);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("LINE = \"%s\"\n", line);
// 		free(line);
// 	}
// 	printf("LINE = \"%s\"\n", line);
// 	close(fd);
// 	return (0);
// }

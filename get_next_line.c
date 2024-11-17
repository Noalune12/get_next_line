#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// extract exactly one line

char	*get_line(char *content)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	if (!content[len])
		return (NULL);
	while (content[len])
		len++;
	line = ft_calloc(len + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '\n')
	{
		line[i] = content[i];
		i++;
	}
	if (content[i] && content[i] == '\n')
	{
		line[i] = '\n';
		line[++i] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

// read file until \n with BUFFER_SIZE

char	*read_file(int fd)
{
	char	*buffer;
	char	*content;
	char	*temp;
	int		b_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	b_read = 1;
	content = NULL;
	while (b_read > 0)
	{
		b_read =read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[b_read] = '\0';
		temp = ft_strjoin(content, buffer);
		if (content)
			free(content);
		content = temp;
		if (ft_strrchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (content);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int		fd;
	char	*line;

	//read only one line
	printf("READ FILE UNTIL 1st \\n\n\n");
	fd = open(argv[1], O_RDONLY);
	line = read_file(fd);
	printf("LINE = %s", line);
	free(line);
	close(fd);

	//get line
	printf("\n\nGET 1ST LINE\n\n");
	char *content;
	fd = open(argv[1], O_RDONLY);
	content = read_file(fd);
	printf("CONTENT = %s\n", content);
	line = get_line(content);
	printf("LINE = '%s'", line);
	free(content);
	free(line);
	close(fd);
	return (0);
}

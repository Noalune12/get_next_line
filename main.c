#include "get_next_line.h"

// char	*get_next_line(int fd)
// {
// 	static char	*remaining_content;
// 	char		*line;
// 	char		buffer[BUFFER_SIZE + 1];

// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
// 	{
// 		if (remaining_content)
// 		{
// 			free(remaining_content);
// 			remaining_content = NULL;
// 		}
// 		return (NULL);
// 	}
// 	remaining_content = read_file(fd, remaining_content, buffer);
// 	if (!remaining_content)
// 		return (NULL);
// 	line = get_line(remaining_content);
// 	remaining_content = update_buffer(remaining_content);
// 	return (line);
// }

#include <fcntl.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int		fd;
	char	*line;

	//get next line
	printf("\n\nGET NEXT LINE\n\n");
	fd = open(argv[1], O_RDONLY);
	printf("fd = %d\n\n", fd);
	//while ((line = get_next_line(fd)) != NULL)
	//{
		line = get_next_line(fd);
		printf("LINE = \"%s\"\n", line);
		free(line);
	//}
	//printf("LINE = \"%s\"\n", line);
	close(fd);
	return (0);
}

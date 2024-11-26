#include "get_next_line.h"
#include "get_next_line_bonus.h"

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

	// //read only one line
	// printf("READ FILE UNTIL 1st \\n\n\n");
	// fd = open(argv[1], O_RDONLY);
	// line = read_file(fd);
	// printf("LINE = %s", line);
	// free(line);
	// close(fd);

	// //get line
	// printf("\n\nGET 1ST LINE\n\n");
	// char *content;
	// fd = open(argv[1], O_RDONLY);
	// content = read_file(fd);
	// printf("CONTENT = %s\n", content);
	// line = get_line(content);
	// printf("LINE = '%s'", line);
	// free(content);
	// free(line);
	// close(fd);

	// //get linesfd
	// printf("\n\nGET LINES\n\n");
	// fd = open(argv[1], O_RDONLY);
	// while (1)
	// {
	// 	content = read_file(fd);
	// 	if (!content)
	// 		break ;
	// 	printf("CONTENT = %s\n", content);
	// 	line = get_line(content);
	// 	if (!line)
	// 		break ;
	// 	printf("LINE = '%s'", line);
	// 	content = update_buffer(content);
	// 	printf("\nCONTENT = %s\n\n", content);
	// 	free(line);
	// 	free(content);
	// }

	// free(content);
	// free(line);
	// close(fd);

	//get next line
	printf("\n\nGET NEXT LINE\n\n");
	fd = open(argv[1], O_RDONLY);
	printf("fd = %d\n\n", fd);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE = \"%s\"\n", line);
		free(line);
	}
	printf("LINE = \"%s\"\n", line);
	close(fd);
	return (0);
}

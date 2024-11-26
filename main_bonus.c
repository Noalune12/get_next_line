#include "get_next_line_bonus.h"

#include <fcntl.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);

	int		fd1;
	int		fd2;
	char	*line;

	//get next line
	printf("\n\nGET NEXT LINE\n\n");
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	printf("fd1 = %d && fd2 = %d\n\n", fd1, fd2);
	while (line != NULL)
	{
		line = get_next_line(fd1);
		printf("LINE fd1 = \"%s\"\n", line);
		free(line);
		line = get_next_line(fd2);
		printf("LINE fd2 = \"%s\"\n", line);
		free(line);
	}
	close(fd1);
	close(fd2);
	return (0);
}

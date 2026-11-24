#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char *line;
	char *line1;
	char *line2;
	int fd = open("txt.txt", O_RDONLY);
	line = get_next_line(fd);
	line1 = get_next_line(fd);
	line2 = get_next_line(fd);
	printf("%s\n", line);
	printf("%s\n", line1);
	printf("%s\n", line2);
	free(line);
	free(line1);
	free(line2);
	return (0);
}
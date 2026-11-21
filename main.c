#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char buff[11];
	int fd = open("txt.txt", O_CREAT | O_RDWR, 0664);
	read(fd, buff, 10);
	printf("%s\n", buff);
}
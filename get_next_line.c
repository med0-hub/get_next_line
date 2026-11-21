#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*get_line(const char *s)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] || s[i] == '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	int			i;
	int			found;
	static char *box;
	char		*line;

	found = 0;
	box = '\0';
	while (found == 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		i = 0;
		buff[BUFFER_SIZE + 1] = '\0';
		box = ft_strjoin(box, buff);
		i = 0;
		while (i < bytes_read)
		{
			if (buff[i] == '\n')
			{
				found = 1;
				break;
			}
			i++;
		}
	}
	line = get_line(box);
	return (line);
}
// if (fd <= 0)
// 		return (NULL);
// 	if (BUFFER_SIZE < 0)
// 		return (NULL);
	
// 	if (bytes_read = -1)
// 	{

// 		return (NULL);
// 	}
// 	if (bytes_read = 0)
// 	{
// 		return (NULL);
// 	}
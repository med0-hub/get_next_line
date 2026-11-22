#include "get_next_line.h"

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
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_rest(char *box)
{
	char	*str;
	int		i;
	int		j;
	int		rest_len;

	if (!box)
		return (NULL);
	i = 0;
	rest_len = 0;
	while (box[i] && box[i] != '\n')
		i++;
	if (box[i] == '\0')
		return (NULL);
	rest_len = ft_strlen(box) - (i + 1);
	str = malloc(sizeof(char) * rest_len + 1);
	if (!str)
		return (NULL);
	j = 0;
	i++;
	while (box[i])
	{
		str[j] = box[i];
		i++;
		j++;
	}
	str[j] = '\0';
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
	char		*tmp;

	found = 0;
	while (found == 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		i = 0;
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(box, buff);
		if (!tmp)
		{
			free(tmp);
			return (NULL);
		}
		free(box);
		box = tmp;
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
	tmp = get_rest(box);
	free(box);
	box = tmp;
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
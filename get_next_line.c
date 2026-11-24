#include "get_next_line.h"

char	*get_line(const char *s, int *error)
{
	char	*str;
	size_t	i;

	if (!s || s[0] == '\0')
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
	{
		*error = 1;
		return (NULL);
	}
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

char	*get_rest(char *box, int *error)
{
	char	*str;
	int		i;
	int		j;
	int		rest_len;

	if (!box || box[0] == '\0')
		return (NULL);
	i = 0;
	rest_len = 0;
	while (box[i] && box[i] != '\n')
		i++;
	if (box[i] == '\0')
		return (NULL);
	rest_len = ft_strlen(box) - (i + 1);
	if (rest_len == 0)
		return (NULL);
	str = malloc(sizeof(char) * rest_len + 1);
	if (!str)
	{
		*error = 1;
		return (NULL);
	}
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
	int			error;
	static char *box;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (is_new_line(box) == 0)
	{
		found = 0;
		while (found == 0)
		{
			bytes_read = read(fd, buff, BUFFER_SIZE);
			if (bytes_read == -1)
			{
				free(box);
				box = NULL;
				return (NULL);
			}
			else if (bytes_read <= 0)
				break;
			i = 0;
			buff[bytes_read] = '\0';
			tmp = ft_strjoin(box, buff);
			if (!tmp)
			{
				free(tmp);
				free(box);
				box = NULL;
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
	}
	error = 0;
	line = get_line(box, &error);
	if (error == 1)
	{
		free(line);
		free(box);
		box = NULL;
		return (NULL);
	}
	tmp = get_rest(box, &error);
	if (error == 1)
	{
		free(line);
		free(box);
		box = NULL;
		return (NULL);
	}
	free(box);
	box = tmp;
	return (line);
}


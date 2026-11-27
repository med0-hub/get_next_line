/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 13:01:11 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/27 13:39:04 by mbelarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*clear_box(char **box, char *other)
{
	free(*box);
	*box = NULL;
	free(other);
	return (NULL);
}

static char	*get_line(const char *s)
{
	char	*str;
	size_t	i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	ft_copy_n(str, s, i);
	return (str);
}

static char	*get_rest(char *box, int *error)
{
	char	*str;
	size_t	i;
	size_t	rest_len;

	if (!box)
		return (NULL);
	i = 0;
	while (box[i] && box[i] != '\n')
		i++;
	if (box[i] == '\0' || box[i + 1] == '\0')
		return (NULL);
	i++;
	rest_len = ft_strlen(box + i);
	str = malloc(rest_len + 1);
	if (!str)
	{
		*error = 1;
		return (NULL);
	}
	ft_copy_n(str, box + i, rest_len);
	return (str);
}

static char	*read_file(int fd, char *box, size_t capacity)
{
	char	*buff;
	char	*tmp;
	ssize_t	bytes_read;

	buff = malloc(capacity + 1);
	if (!buff)
		return (clear_box(&box, NULL));
	while (1)
	{
		bytes_read = read(fd, buff, capacity);
		if (bytes_read < 0)
			return (clear_box(&box, buff));
		if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(box, buff);
		free(box);
		box = tmp;
		if (!box || is_new_line(buff))
			break ;
	}
	free(buff);
	return (box);
}

char	*get_next_line(int fd)
{
	static char	*box[MAX_FD];
	char		*line;
	char		*tmp;
	int			error;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (BUFFER_SIZE <= 0)
		return (clear_box(&box[fd], NULL));
	if (!is_new_line(box[fd]))
		box[fd] = read_file(fd, box[fd], BUFFER_SIZE);
	line = get_line(box[fd]);
	if (!line)
		return (clear_box(&box[fd], NULL));
	error = 0;
	tmp = get_rest(box[fd], &error);
	if (error)
		return (clear_box(&box[fd], line));
	free(box[fd]);
	box[fd] = tmp;
	return (line);
}

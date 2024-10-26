/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:01:54 by chourri           #+#    #+#             */
/*   Updated: 2024/01/19 18:25:05 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read(int fd, char *s)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
			return (free(buffer), free(s), buffer = NULL, s = NULL, NULL);
		buffer[bytes_read] = '\0';
		s = ft_strjoin(s, buffer);
		if (ft_strchr(s, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (s);
}

static char	*ft_get_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_get_remaining(char *str)
{
	char	*remaining;
	char	*new_char_after_newline;
	size_t	remaining_length;

	new_char_after_newline = ft_strchr(str, '\n') + 1;
	if (!ft_strchr(str, '\n'))
		return (free(str), str = NULL, NULL);
	remaining_length = ft_strlen(new_char_after_newline) + 1;
	remaining = malloc(remaining_length);
	if (!remaining)
		return (free(str), str = NULL, NULL);
	ft_memcpy(remaining, new_char_after_newline, remaining_length);
	free(str);
	str = NULL;
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1 || BUFFER_SIZE > INT_MAX
		|| fd < 0 || fd > OPEN_MAX)
	{
		if (str[fd])
			return (free(str[fd]), str[fd] = NULL, NULL);
		return (NULL);
	}
	str[fd] = ft_read(fd, str[fd]);
	if (!str[fd] || !(*str[fd]))
		return (free(str[fd]), str[fd] = NULL, NULL);
	line = ft_get_line(str[fd]);
	if (!line || !line[0])
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = ft_get_remaining(str[fd]);
	return (line);
}

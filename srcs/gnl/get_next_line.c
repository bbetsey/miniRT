/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:02:06 by bbetsey           #+#    #+#             */
/*   Updated: 2021/02/19 14:01:33 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	char	*buf_strjoin;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	strjoin = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*s1)
		*strjoin++ = *s1++;
	while (*s2)
		*strjoin++ = *s2++;
	*strjoin = '\0';
	return (buf_strjoin);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	array = malloc(count * size);
	if (!array)
		return (0);
	return (ft_bzero(array, count * size));
}

char	*check_remain(char **remain, char **line)
{
	char	*new_line;

	new_line = NULL;
	if (*remain)
	{
		if ((new_line = ft_strchr(*remain, '\n')))
		{
			*new_line = '\0';
			*line = ft_strdup(*remain);
			ft_strcpy(*remain, ++new_line);
		}
		else
		{
			*line = ft_strdup(*remain);
			free(*remain);
			*remain = 0;
		}
	}
	else
		*line = ft_calloc(1, sizeof(char));
	return (new_line);
}

void	append_line(char **buf, char **new_line, char **line, char **remain)
{
	char	*tmp;

	if ((*new_line = ft_strchr(*buf, '\n')))
	{
		**new_line = '\0';
		*remain = ft_strdup(++(*new_line));
	}
	tmp = *line;
	*line = ft_strjoin(*line, *buf);
	free(tmp);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	int			read_bytes;
	char		*new_line;
	static char	*remain;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if ((new_line = check_remain(&remain, line)))
		return (1);
	if (!(buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
		return (-1);
	while (!new_line && ((read_bytes = read(fd, buf, BUFFER_SIZE))) > 0)
	{
		buf[read_bytes] = '\0';
		append_line(&buf, &new_line, line, &remain);
	}
	free(buf);
	if (read_bytes < 0)
		return (-1);
	if (read_bytes == 0 && !remain)
		return (0);
	return (1);
}

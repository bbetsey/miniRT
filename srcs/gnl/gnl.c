/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:02:06 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 15:13:51 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strjoin(char const *s1, char const s2)
{
	char	*strjoin;
	char	*buf_strjoin;
	int		s1_len;

	s1_len = ft_strlen((char *)s1);
	strjoin = malloc((s1_len + 2) * sizeof(char));
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*s1)
		*strjoin++ = *s1++;
	*strjoin++ = s2;
	*strjoin = '\0';
	return (buf_strjoin);
}

int	get_next_line(int fd, char **line)
{
	char	buf;
	char	*tmp;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_calloc(1, sizeof(char));
	while (read(fd, &buf, 1) > 0)
	{
		if (buf != '\n')
		{
			tmp = *line;
			*line = ft_strjoin(*line, buf);
			free(tmp);
		}
		else
			return (1);
	}
	return (0);
}

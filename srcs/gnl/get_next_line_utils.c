/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:11:07 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 15:10:05 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*buf;

	buf = s;
	while (n > 0)
	{
		*buf = '\0';
		buf++;
		n--;
	}
	return (s);
}

size_t	ft_strlen(const char *str)
{
	size_t		len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	array = malloc(count * size);
	if (!array)
		return (0);
	return (ft_bzero(array, count * size));
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (unsigned char)c)
		return ((char *)str);
	return (0);
}

char	*ft_strdup(const char *str)
{
	int		len;
	char	*copy;
	char	*buf_copy;

	len = ft_strlen((char *)str);
	copy = malloc((len + 1) * sizeof(char));
	if (!copy)
		return (0);
	buf_copy = copy;
	while (*str)
	{
		*copy = *str;
		copy++;
		str++;
	}
	*copy = '\0';
	return (buf_copy);
}

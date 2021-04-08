/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:11:07 by bbetsey           #+#    #+#             */
/*   Updated: 2021/02/02 15:26:51 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		*ft_bzero(void *s, size_t n)
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

size_t		ft_strlen(const char *str)
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

char		*ft_strcpy(char *dst, char *src)
{
	char	*buf_dst;

	if (!dst)
		return (0);
	buf_dst = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (buf_dst);
}

char		*ft_strchr(const char *str, int c)
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

char		*ft_strdup(const char *str)
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

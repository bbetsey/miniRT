/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:04:15 by bbetsey           #+#    #+#             */
/*   Updated: 2021/02/20 14:29:05 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char		**make_arr(char const *s, char *c)
{
	int		i;
	char	**arr;

	i = 0;
	while (*s)
	{
		if (*s == c[0] || *s == c[1])
			s++;
		else
		{
			i++;
			while (*s && *s != c[0] && *s != c[1])
				s++;
		}
	}
	arr = malloc((i + 1) * sizeof(char *));
	if (!arr)
	{
		free(arr);
		return (0);
	}
	return (arr);
}

static char		**fail_malloc(char **arr, int i)
{
	int		n;

	n = 0;
	while (n < i)
	{
		free(arr[n]);
		n++;
	}
	free(arr);
	return (0);
}

static char		*make_str(char const *s, char *c, char **arr, int i)
{
	int		str_len;
	char	*str;
	char	*buf_s;
	char	*buf_str;

	str_len = 0;
	buf_s = (char *)s;
	while (*s && *s != c[0] && *s++ != c[1])
		str_len++;
	str = malloc((str_len + 1) * sizeof(char));
	if (!str)
	{
		free(str);
		fail_malloc(arr, i);
		return (0);
	}
	str[str_len] = '\0';
	buf_str = str;
	while (str_len--)
		*(str++) = *(buf_s++);
	return (buf_str);
}

char			**rt_split(char const *s, char *c)
{
	char	**arr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	arr = make_arr(s, c);
	if (!arr)
		return (0);
	while (*s)
	{
		if (*s == c[0] || *s == c[1])
			s++;
		else
		{
			if (!(arr[i] = make_str(s, c, arr, i)))
				return (0);
			i++;
			while (*s && *s != c[0] && *s != c[1])
				s++;
		}
	}
	arr[i] = 0;
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:44:38 by bbetsey           #+#    #+#             */
/*   Updated: 2021/02/20 17:06:59 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
		c == '\r' || c == ' ')
		return (1);
	return (0);
}

float		rt_atof(char *str)
{
	float	n;
	int		sign;

	n = 0.0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
		n = n * 10.0 + (*str++ - 48);
	if (*str++ == '.')
	{
		if (*str >= 48 && *str <= 57)
		{
			n = n * 10.0 + (*str - 48);
			return (n / 10.0 * sign);
		}
	}
	return (n * sign);
}

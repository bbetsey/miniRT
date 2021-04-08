/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:14:31 by bbetsey           #+#    #+#             */
/*   Updated: 2021/02/20 14:29:48 by bbetsey          ###   ########.fr       */
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

int			rt_atoi(const char *str)
{
	int		sign;
	long	result;
	long	next;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		next = result * 10 + (*str - 48);
		if (next < result)
			return (sign < 0 ? 0 : -1);
		result = next;
		str++;
	}
	return (int)(result * sign);
}

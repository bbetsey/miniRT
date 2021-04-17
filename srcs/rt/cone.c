/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:48:57 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/17 16:52:34 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	co_closest(double x1, double x2, float min, float max)
{
	if (x1 >= min && x1 <= max)
	{
		if (x2 >= min && x2 <= max)
		{
			if (x1 < x2)
				return (x1);
			else
				return (x2);
		}
		return (x1);
	}
	else if (x2 >= min && x2 <= max)
		return (x2);
	else
		return (0);
}

t_closest	co_intersect(void *data, t_vector eye, t_vector dir, t_limit lim)
{
	t_closest	closest;

	(void)data;
	(void)eye;
	(void)dir;
	(void)lim;
	closest.length = 0;
	return (closest);
}

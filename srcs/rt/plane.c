/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:09:15 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/11 00:45:14 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	pl_closest(t_limit lim, float t, t_closest *closest, t_pl *pl)
{
	if (t >= lim.min && t <= lim.max)
	{
		closest->length = t;
		closest->rgb = pl->rgb;
		closest->color = 1;
		return (t);
	}
	return (0);
}

t_closest	pl_intersect(void *data, t_vector eye, t_vector dir, t_limit lim)
{
	t_closest	closest;
	t_pl		*plane;
	t_quadro	s;
	double		t;

	plane = data;
	plane->n_vec = vec_norm(plane->n_vec);
	s.a = vec_dot(vec_sub(eye, plane->vec), plane->n_vec);
	s.b = vec_dot(dir, plane->n_vec);
	closest.length = 0;
	if (fabs(s.b) < 0.00001 || (s.a < -0.00001 && s.b < -0.00001)
		|| (s.a > 0.00001 && s.b > 0.00001))
		return (closest);
	t = (-1) * s.a / s.b;
	if (t >= 0)
	{
		if (pl_closest(lim, t, &closest, plane))
		{
			closest.intersect = vec_sum(eye, vec_multi(dir, t));
			closest.norm = plane->n_vec;
			return (closest);
		}
	}
	return (closest);
}

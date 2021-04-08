/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:09:15 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/02 18:52:36 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		pl_closest(t_limit lim, float t, t_closest *closest, t_pl *pl)
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
	plane->n_vec = rotate_normal(dir, vec_norm(plane->n_vec));
	s.a = vec_dot(vec_sub(eye, plane->vec), plane->n_vec);
	s.b = vec_dot(dir, plane->n_vec);
	closest.length = 0;
	if (fabs(s.b) < 0.0001 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
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

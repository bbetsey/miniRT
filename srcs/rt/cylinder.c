/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 04:10:39 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/02 19:04:52 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		cy_closest(double x1, double x2, float min, float max)
{
	if (x1 >= min && x1 <= max)
	{
		if (x2 >= min && x2 <= max)
			return (x1 < x2 ? x1 : x2);
		return (x1);
	}
	else if (x2 >= min && x2 <= max)
		return (x2);
	else
		return (0);
}

t_closest	cy_data(t_closest closest, t_cy *cy, t_vector eye, t_vector dir)
{
	double		x;
	t_vector	b;
	t_vector	point;

	closest.intersect = vec_sum(eye, vec_multi(dir, closest.length));
	b = vec_sum(cy->vec, vec_multi(cy->n_vec, cy->h));
	x = vec_dot(vec_sub(closest.intersect, b), cy->n_vec);
	point = vec_sum(b, vec_multi(cy->n_vec, x));
	closest.norm = vec_norm(vec_sub(closest.intersect, point));
	closest.norm = rotate_normal(dir, closest.norm);
	closest.rgb = cy->rgb;
	closest.color = 1;
	return (closest);
}

t_closest	cy_intersect(void *data, t_vector eye, t_vector dir, t_limit lim)
{
	t_closest	closest;
	t_cy_eq		s;
	t_cy		*cy;

	cy = data;
	closest.length = 0;
	s.sub = vec_sub(eye, cy->vec);
	s.a = vec_dot(dir, dir) - pow(vec_dot(dir, cy->n_vec), 2.0);
	s.b = (vec_dot(dir, s.sub) - vec_dot(dir, cy->n_vec) *
	vec_dot(s.sub, cy->n_vec)) * 2.;
	s.c = vec_dot(s.sub, s.sub) - pow(vec_dot(s.sub, cy->n_vec), 2.0)
	- pow(cy->d / 2.0, 2.0);
	s.d = pow(s.b, 2.0) - 4 * s.a * s.c;
	if (s.d < 0)
		return (closest);
	s.x1 = (-s.b - sqrt(s.d)) / (2 * s.a);
	s.x2 = (-s.b + sqrt(s.d)) / (2 * s.a);
	s.z1 = vec_dot(dir, cy->n_vec) * s.x1 + vec_dot(s.sub, cy->n_vec);
	s.z2 = vec_dot(dir, cy->n_vec) * s.x2 + vec_dot(s.sub, cy->n_vec);
	s.x1 = (s.z1 < 0 || s.z1 > cy->h) ? INFINITY : s.x1;
	s.x2 = (s.z2 < 0 || s.z2 > cy->h) ? INFINITY : s.x2;
	if (!(closest.length = cy_closest(s.x1, s.x2, lim.min, lim.max)))
		return (closest);
	return (cy_data(closest, cy, eye, dir));
}

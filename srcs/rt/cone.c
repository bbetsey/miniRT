/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:48:57 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/16 16:55:17 by bbetsey          ###   ########.fr       */
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

// t_closest	co_solution(t_closest closest, t_object *cone)
// {
// 	closest.
// }

t_closest	co_check(t_co_eq eq, t_limit lim, t_co *cone)
{
	t_closest	closest;
	t_closest	solution;
	t_pl		plane;

	closest.length = co_closest(eq.x1, eq.x2, lim.min, lim.max);
	if (!closest.length)
		return (closest);
	closest.intersect = vec_sum(eq.eye, vec_multi(eq.dir, closest.length));
	plane.n_vec = cone->n_vec;
	plane.vec = cone->vec;
	plane.rgb = cone->rgb;
	plane.ref = cone->ref;
	plane.spec = cone->spec;
	solution = pl_intersect(&plane, closest.intersect, cone->n_vec, lim);
	if (solution.length <= cone->h)
		return (solution);
	return ((t_closest){0, 0, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, 0});
}

t_closest	co_intersect(void *data, t_vector eye, t_vector dir, t_limit lim)
{
	t_co_eq		eq;
	t_co		*cone;
	t_closest	closest;
	t_closest	solution;

	cone = (t_co *)data;
	solution.length = 0;
	eq.k = cos(((cone->d / 2) * M_PI) / 180);
	eq.w = vec_sub(eye, cone->vec);
	eq.a = pow(vec_dot(dir, cone->n_vec), 2) - powf(eq.k, 2.);
	eq.b = 2.0 * (vec_dot(dir, cone->n_vec) * vec_dot(eq.w, cone->n_vec) - vec_dot(dir, eq.w) * powf(eq.k, 2.));
	eq.c = pow(vec_dot(eq.w, cone->n_vec), 2) - vec_dot(eq.w, eq.w) * powf(eq.k, 2.);
	eq.d = powf(eq.b, 2.) - (4. * eq.a * eq.c);
	if (eq.d < 0)
		return (solution);
	eq.x1 = (-eq.b - eq.d) / (2.0 * eq.a);
	eq.x2 = (-eq.b + eq.d) / (2.0 * eq.a);
	closest.length = co_closest(eq.x1, eq.x2, lim.min, lim.max);
	if (!closest.length)
		return (solution);
	closest.intersect = vec_sum(eye, vec_multi(dir, closest.length));
	eq.cp = vec_sub(vec_sum(eye, closest.intersect), cone->vec);
	eq.m = vec_dot(eq.cp, cone->n_vec);
	if (eq.m < 0 || eq.m > cone->h)
		return (solution);
	closest.norm = vec_norm(vec_sub(vec_multi(eq.cp, vec_dot(cone->n_vec, eq.cp) / vec_dot(eq.cp, eq.cp)), cone->n_vec));
	closest.rgb = cone->rgb;
	closest.ref = cone->ref;
	closest.spec = cone->spec;
	return (closest);


	// eq.k = tan(((cone->d / 2) * M_PI) / 180);
	// eq.w = vec_sub(eye, cone->vec);
	// eq.a = vec_dot(dir, dir) - (1 + eq.k * eq.k) + pow(vec_dot(dir, cone->n_vec), 2);
	// eq.b = 2 * (vec_dot(dir, eq.w) - (1 + eq.k * eq.k) * vec_dot(dir, cone->n_vec) * vec_dot(eq.w, cone->n_vec));
	// eq.c = vec_dot(eq.w, eq.w) - (1 + eq.k * eq.k) * pow(vec_dot(eq.w, cone->n_vec), 2);
	// eq.d = pow(eq.b, 2) - (4 * eq.a * eq.c);
	// if (eq.d < 0)
	// 	return (closest);
	// eq.d = sqrt(eq.d);
	// eq.x1 = (-eq.b - eq.d) / (2.0 * eq.a);
	// eq.x2 = (-eq.b + eq.d) / (2.0 * eq.a);
	// closest.length = co_closest(eq.x1, eq.x2, lim.min, lim.max);
	// if (!closest.length)
	// 	return (closest);
	// closest.intersect = vec_sum(eye, vec_multi(dir, closest.length));
	// closest.norm = rotate_normal(dir, cone->n_vec);
	// closest.rgb = cone->rgb;
	// closest.ref = cone->ref;
	// closest.spec = cone->spec;
	// return (closest);

	// eq.eye = eye;
	// eq.dir = dir;
	// eq.m = pow(cone->d / 2, 2) / pow(cone->h, 2);
	// eq.w = vec_sub(eye, cone->vec);
	// eq.t1 = vec_dot(dir, cone->n_vec);
	// eq.t2 = vec_dot(eq.w, cone->n_vec);
	// eq.a = pow(eq.t1, 2);
	// eq.a = vec_dot(dir, dir) - eq.m * eq.a - eq.a;
	// eq.b = 2 * (vec_dot(dir, eq.w) - eq.m * eq.t1 * eq.t2 - eq.t1 * eq.t2);
	// eq.c = vec_dot(eq.w, eq.w) - eq.m * pow(eq.t2, 2) - pow(eq.t2, 2);
	// eq.d = pow(eq.b, 2) - (4 * eq.a * eq.c);
	// if (eq.d < 0)
	// 	return ((t_closest){0, 0, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, 0});
	// eq.d = sqrt(eq.d);
	// eq.x1 = (-eq.b - eq.d) / (2.0 * eq.a);
	// eq.x2 = (-eq.b + eq.d) / (2.0 * eq.a);
	// return (co_check(eq, lim, cone));
}

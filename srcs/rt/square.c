/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:49:11 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/12 00:42:00 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sq_closest(t_limit lim, double t, t_closest *closest, t_sq *sq)
{
	if (t >= lim.min && t <= lim.max)
	{
		closest->color = 1;
		closest->rgb = sq->rgb;
		closest->length = t;
		return (t);
	}
	return (0);
}

t_closest	sq_intersect(void *data, t_vector eye, t_vector dir, t_limit lim)
{
	t_closest		closest;
	t_sq_eq			s;
	t_sq			*sq;

	closest.length = 0;
	sq = data;
	sq->n_vec = vec_norm(sq->n_vec);
	s.a = vec_dot(vec_sub(eye, sq->vec), sq->n_vec);
	s.b = vec_dot(dir, sq->n_vec);
	if (fabs(s.b) < 0.00001 || (s.a < -0.00001 && s.b < -0.00001)
		|| (s.a > 0.00001 && s.b > 0.00001))
		return (closest);
	s.x1 = -s.a / s.b;
	s.vec = vec_sub(vec_sum(vec_multi(dir, s.x1), eye), sq->vec);
	s.x2 = sq->side / 2.;
	if (fabs(s.vec.x) > s.x2 || fabs(s.vec.y) > s.x2 || fabs(s.vec.z) > s.x2)
		return (closest);
	if (sq_closest(lim, s.x1, &closest, sq))
	{
		closest.intersect = vec_sum(eye, vec_multi(dir, s.x1));
		closest.norm = rotate_normal(dir, sq->n_vec);
		return (closest);
	}
	return (closest);
}

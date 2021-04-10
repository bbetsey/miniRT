/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:45:02 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/10 16:38:49 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sp_closest(double x1, double x2, float min, float max)
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

void	sp_fill_data(t_vector eye, t_vector dir, t_closest *rs, t_sp *sp)
{
	rs->rgb = sp->rgb;
	rs->intersect = vec_sum(eye, vec_multi(dir, rs->length));
	rs->norm = rotate_normal(dir, vec_norm(vec_sub(rs->intersect, sp->vec)));
	rs->color = 1;
}

t_closest	sp_intersect(void *data, t_vector eye, t_vector dir, t_limit lim)
{
	t_vector	cam_sp;
	t_closest	rs;
	t_quadro	equ;
	t_sp		*sp;

	sp = data;
	cam_sp = vec_sub(eye, sp->vec);
	equ.a = vec_dot(dir, dir);
	equ.b = 2 * (vec_dot(cam_sp, dir));
	equ.c = vec_dot(cam_sp, cam_sp) - pow((sp->d / 2), 2);
	equ.d = pow(equ.b, 2) - 4 * equ.c * equ.a;
	if (equ.d >= 0)
	{
		equ.x1 = (-equ.b + sqrt(equ.d)) / (2. * equ.a);
		equ.x2 = (-equ.b - sqrt(equ.d)) / (2. * equ.a);
		rs.length = sp_closest(equ.x1, equ.x2, lim.min, lim.max);
		if (!rs.length)
			return (rs);
		sp_fill_data(eye, dir, &rs, sp);
	}
	else
		rs.length = 0;
	return (rs);
}

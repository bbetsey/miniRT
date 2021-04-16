/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:43:23 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/15 21:36:55 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	tr_closest(t_limit lim, double t, t_closest *closest, t_tr *tr)
{
	if (t >= lim.min && t <= lim.max)
	{
		closest->color = 1;
		closest->rgb = tr->rgb;
		closest->spec = tr->spec;
		closest->ref = tr->ref;
		return (t);
	}
	return (0);
}

int	tr_check(t_tr *tr, t_vector intersect, t_vector norm)
{
	t_vector	tmp;

	tmp = vec_cross(vec_sub(tr->v2, tr->v1), vec_sub(intersect, tr->v1));
	if (vec_dot(norm, tmp) < -0.0001)
		return (0);
	tmp = vec_cross(vec_sub(tr->v3, tr->v2), vec_sub(intersect, tr->v2));
	if (vec_dot(norm, tmp) < -0.0001)
		return (0);
	tmp = vec_cross(vec_sub(tr->v1, tr->v3), vec_sub(intersect, tr->v3));
	if (vec_dot(norm, tmp) < -0.0001)
		return (0);
	return (1);
}

t_closest	tr_intersect(void *data, t_vector eye, t_vector dir, t_limit lim)
{
	t_tr		*tr;
	t_closest	closest;
	t_closest	tmp;

	tr = data;
	closest.length = 0;
	tr->pl.n_vec = tr->norm;
	tr->pl.vec = tr->v1;
	tr->pl.rgb = tr->rgb;
	tmp = pl_intersect(&(tr->pl), eye, dir, lim);
	if (tmp.length && tr_check(tr, tmp.intersect, tr->norm))
	{
		tmp.norm = rotate_normal(dir, tr->norm);
		return (tmp);
	}
	return (closest);
}

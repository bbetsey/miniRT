/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:17:54 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/11 00:26:13 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_closest	find_closest(t_closest solution, t_closest closest)
{
	if (solution.length)
	{
		if (solution.length < closest.length)
		{
			closest.length = solution.length;
			closest.rgb = solution.rgb;
			closest.intersect = solution.intersect;
			closest.norm = solution.norm;
			closest.color = solution.color;
		}
	}
	return (closest);
}

int	intersect(t_scene *scene, t_vector ray)
{
	t_object	*obj;
	t_closest	closest;
	t_closest	solution;
	t_color		tmp;
	t_limit		lim;

	obj = scene->objs;
	closest.color = BACKCOLOR;
	closest.length = INFINITY;
	lim.min = 1;
	lim.max = INFINITY;
	while (obj)
	{
		solution = obj->equation(obj->data, scene->cams->vec,
				ray, lim);
		closest = find_closest(solution, closest);
		obj = obj->next;
	}
	if (closest.color != BACKCOLOR)
	{
		tmp = compute_color(closest, scene, ray);
		closest.color = create_trgb(0, tmp.r, tmp.g, tmp.b);
	}
	return (closest.color);
}

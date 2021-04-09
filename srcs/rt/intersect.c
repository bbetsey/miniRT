/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:17:54 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 15:42:22 by bbetsey          ###   ########.fr       */
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

int	intersect(t_scene *scene)
{
	t_object	*obj;
	t_closest	closest;
	t_closest	solution;
	t_color		tmp;

	obj = scene->objs;
	closest.color = BACKCOLOR;
	closest.length = INFINITY;
	scene->lim.min = 1;
	scene->lim.max = INFINITY;
	while (obj)
	{
		solution = obj->equation(obj->data, scene->cams->vec,
				scene->ray, scene->lim);
		closest = find_closest(solution, closest);
		obj = obj->next;
	}
	if (closest.color != BACKCOLOR)
	{
		tmp = compute_color(closest, scene);
		closest.color = create_trgb(0, tmp.r, tmp.g, tmp.b);
	}
	return (closest.color);
}

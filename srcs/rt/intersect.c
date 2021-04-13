/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:17:54 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/13 18:37:38 by bbetsey          ###   ########.fr       */
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

t_color	intersect(t_scene *scene, t_vector ray)
{
	t_object	*obj;
	t_closest	closest;
	t_closest	solution;
	t_color		tmp;
	t_limit		lim;

	obj = scene->objs;
	closest.color = BACKCOLOR;
	closest.length = INFINITY;
	closest.rgb = (t_color){0, 0, 0};
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
		closest.rgb = tmp;
	}
	return (closest.rgb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:17:54 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/15 20:53:17 by bbetsey          ###   ########.fr       */
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
			closest.spec = solution.spec;
			closest.ref = solution.ref;
		}
	}
	return (closest);
}

t_color	intersect(t_scene *scene, t_ray ray, t_limit lim,
int recursive)
{
	t_object	*obj;
	t_closest	closest;
	t_closest	solution;
	t_vector	refl_ray;
	t_color		res;

	obj = scene->objs;
	closest.color = BACKCOLOR;
	closest.length = INFINITY;
	closest.rgb = (t_color){0, 0, 0};
	while (obj)
	{
		solution = obj->equation(obj->data, ray.eye, ray.dir, lim);
		closest = find_closest(solution, closest);
		obj = obj->next;
	}
	if (closest.color != BACKCOLOR)
		closest.rgb = compute_color(closest, scene, ray.dir);
	if (recursive <= 0 || closest.ref <= 0)
		return (closest.rgb);
	refl_ray = vec_norm(reflect_ray(vec_multi(ray.dir, -1), closest.norm));
	res = intersect(scene, (t_ray){closest.intersect,
			refl_ray}, (t_limit){0.001, INFINITY}, recursive - 1);
	return (color_sum(color_multi(closest.rgb,
				1 - closest.ref), color_multi(res, closest.ref)));
}

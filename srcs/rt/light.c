/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:24:11 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/17 17:36:14 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect_ray(t_vector r, t_vector n)
{
	return (vec_sub(vec_multi(n, 2.0 * vec_dot(n, r)), r));
}

float	light_point(t_vector n, t_vector l, float ratio)
{
	float	dot;

	dot = vec_dot(n, l);
	if (dot > 0.0001)
		return (ratio * dot / (vec_len(l) * vec_len(n)));
	return (0);
}

float	make_specular(t_specular spec)
{
	float		dot;
	t_vector	r;
	t_vector	v;

	r = reflect_ray(spec.l, spec.n);
	v = vec_multi(spec.ray, -1);
	dot = vec_dot(r, v);
	if (dot > 0.0001)
		return (spec.rat * pow(vec_dot(r, v) / (vec_len(r) * vec_len(v)),
				spec.spec));
	return (0);
}

float	compute_lightning(t_scene *scene, t_light *light,
t_closest solution, t_tmp tmp)
{
	float		i;
	t_vector	l;
	t_object	*obj;
	t_closest	closest;
	t_limit		lim;

	l = vec_sub(light->vec, solution.intersect);
	obj = scene->objs;
	lim.min = 0.0001;
	lim.max = 1;
	i = 0.0;
	while (obj)
	{
		closest = obj->equation(obj->data, solution.intersect, l, lim);
		if (closest.length)
			return (i);
		obj = obj->next;
	}
	i += light_point(tmp.n, l, light->ratio);
	i += make_specular((t_specular){tmp.n, l, tmp.ray, light->ratio,
			solution.spec});
	return (i);
}

t_color	compute_color(t_closest closest, t_scene *scene, t_vector ray)
{
	float		i;
	t_color		ret;
	t_light		*light;

	light = scene->light;
	ret = color_mix(closest.rgb, color_multi(scene->amb.rgb, scene->amb.ratio));
	while (light)
	{
		i = compute_lightning(scene, light, closest,
				(t_tmp){ray, closest.norm});
		ret = color_sum(ret, color_mix(closest.rgb,
					color_multi(light->rgb, i)));
		light = light->next;
		i = 0.0;
	}
	return (ret);
}

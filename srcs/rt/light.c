/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:24:11 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 15:43:31 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	light_point(t_vector n, t_vector l, float ratio)
{
	float	dot;

	dot = vec_dot(n, l);
	if (dot > 0)
		return (ratio * dot / (vec_len(l) * vec_len(n)));
	return (0);
}

float	make_specular(t_vector n, t_vector l, t_vector ray, float rat)
{
	float		dot;
	t_vector	r;
	t_vector	v;

	r = vec_sub(vec_multi(n, 2 * vec_dot(n, l)), l);
	v = vec_multi(ray, -1);
	dot = vec_dot(r, v);
	if (dot > 0)
		return (rat * pow(vec_dot(r, v) / (vec_len(r) * vec_len(v)), SPECULAR));
	return (0);
}

float	compute_lightning(t_scene *scene, t_light *light,
t_vector intersect, t_vector n)
{
	float		i;
	t_vector	l;
	t_object	*obj;
	t_closest	closest;

	l = vec_sub(light->vec, intersect);
	obj = scene->objs;
	scene->lim.min = 0.0001;
	scene->lim.max = 1;
	i = 0.0;
	while (obj)
	{
		closest = obj->equation(obj->data, intersect, l, scene->lim);
		if (closest.length)
			return (i);
		obj = obj->next;
	}
	i += light_point(n, l, light->ratio);
	i += make_specular(n, l, scene->ray, light->ratio);
	return (i);
}

t_color	compute_color(t_closest closest, t_scene *scene)
{
	float		i;
	t_color		ret;
	t_light		*light;

	light = scene->light;
	ret = color_mix(closest.rgb, color_multi(scene->amb.rgb, scene->amb.ratio));
	while (light)
	{
		i = compute_lightning(scene, light, closest.intersect, closest.norm);
		ret = color_sum(ret, color_mix(closest.rgb,
					color_multi(light->rgb, i)));
		light = light->next;
		i = 0.0;
	}
	return (ret);
}

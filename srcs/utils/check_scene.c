/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:16:23 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/08 21:48:56 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_rgb(t_color rgb, t_scene *scene)
{
	if (rgb.r < 0 || rgb.r > 255)
		error_handler("wrong RGB", scene);
	if (rgb.g < 0 || rgb.g > 255)
		error_handler("wrong RGB", scene);
	if (rgb.b < 0 || rgb.b > 255)
		error_handler("wrong RGB", scene);
}

void		check_scene(t_scene *scene)
{
	t_light		*light;

	if (scene->cams == 0)
		error_handler("No one camera", scene);
	if (!(scene->amb.check) || !(scene->res.check) || !(scene->light))
		error_handler("No ambient or resolution or light", scene);
	check_rgb(scene->amb.rgb, scene);
	light = scene->light;
	if (!light)
		error_handler("no light!", scene);
	while (light)
	{
		check_rgb(light->rgb, scene);
		if (light->ratio < 0 || light->ratio > 1)
			error_handler("light ratio is set incorrect", scene);
		light = light->next;
	}
}

void		check_normal(t_vector n, t_scene *scene)
{
	if (n.x > 1 || n.x < -1)
		error_handler("wrong normal [-1; 1]", scene);
	if (n.y > 1 || n.y < -1)
		error_handler("wrong normal [-1; 1]", scene);
	if (n.z > 1 || n.z < -1)
		error_handler("wrong normal [-1; 1]", scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:16:23 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/10 16:32:21 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_rgb(t_color rgb, t_scene *scene)
{
	if (rgb.r < 0 || rgb.r > 255)
		error_handler("wrong RGB", scene);
	if (rgb.g < 0 || rgb.g > 255)
		error_handler("wrong RGB", scene);
	if (rgb.b < 0 || rgb.b > 255)
		error_handler("wrong RGB", scene);
}

void	check_scene(t_scene *scene)
{
	t_light		*light;

	if (scene->cams == 0)
		error_handler("No one camera", scene);
	if (!(scene->amb.check) || !(scene->res.check))
		error_handler("No ambient or resolution", scene);
	check_rgb(scene->amb.rgb, scene);
	light = scene->light;
	while (light)
	{
		check_rgb(light->rgb, scene);
		if (light->ratio < 0 || light->ratio > 1)
			error_handler("light ratio is set incorrect", scene);
		light = light->next;
	}
}

void	check_normal(t_vector n, t_scene *scene)
{
	if (n.x > 1 || n.x < -1)
		error_handler("wrong normal [-1; 1]", scene);
	if (n.y > 1 || n.y < -1)
		error_handler("wrong normal [-1; 1]", scene);
	if (n.z > 1 || n.z < -1)
		error_handler("wrong normal [-1; 1]", scene);
}

void	install_start_end_x_y(t_scene *scene)
{
	scene->x_start = scene->res.width / (-2.0);
	scene->x_end = scene->res.width / 2.0;
	scene->y_start = scene->res.height / 2.0;
	scene->y_end = scene->res.height / (-2.0);
}

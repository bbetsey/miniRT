/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:28:41 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/06 21:43:01 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		install_cams(t_scene *scene)
{
	t_cam	*cams;

	cams = scene->cams;
	scene->res.ratio = (float)scene->res.width / (float)scene->res.height;
	while (cams)
	{
		cams->v_width = (double)tan(cams->fov / 2.0 * (M_PI / 180)) * 2.0;
		cams->v_height = (double)cams->v_width / scene->res.ratio;
		cams->x_pixel = (double)cams->v_width / scene->res.width;
		cams->y_pixel = (double)cams->v_height / scene->res.height;
		cams = cams->next;
	}
}

void		trace_ray(t_scene *scene)
{
	t_trace		trace;

	trace.j = 0;
	trace.y = scene->res.height / 2;
	while (trace.y > scene->res.height / (-2))
	{
		trace.i = 0;
		trace.x = scene->res.width / (-2);
		while (trace.x < scene->res.width / 2)
		{
			scene->ray = make_ray(trace.x, trace.y, scene->cams);
			trace.color = intersect(scene);
			my_mlx_pixel_put(&scene->img, trace.i++, trace.j, trace.color);
			trace.x++;
		}
		trace.j++;
		trace.y--;
	}
}

void		draw_image(t_scene *scene, int is_save)
{
	trace_ray(scene);
	if (is_save)
		create_image(scene);
	else
		mlx_put_image_to_window(scene->mlx, scene->window,
		scene->img.img, 0, 0);
}

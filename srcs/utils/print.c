/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:53:34 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 15:25:20 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_cameras(t_scene *scene)
{
	t_cam		*cam;

	cam = scene->cams;
	while (cam)
	{
		printf("Camera:\t\t[%.1f, %.1f, %.1f] [%.1f, %.1f, %.1f] [%.1f]\n",
			cam->vec.x, cam->vec.y, cam->vec.z, cam->n_vec.x,
			cam->n_vec.y, cam->n_vec.z, cam->fov);
		cam = cam->next;
	}
}

void	print_objects(t_scene *scene)
{
	t_object	*obj;

	obj = scene->objs;
	while (obj)
	{
		if (obj->type == PLANE)
			print_plane(obj);
		else if (obj->type == SPHERE)
			print_sphere(obj);
		else if (obj->type == CYLINDER)
			print_cylinder(obj);
		else if (obj->type == TRIANGLE)
			print_triangle(obj);
		else if (obj->type == SQUARE)
			print_square(obj);
		obj = obj->next;
	}
}

void	print_scene(t_scene *scene)
{
	t_light		*light;

	printf("Resolution:\t[%d] [%d]\n", scene->res.width, scene->res.height);
	printf("Ambient:\t[%.1f] [R:%d G:%d B:%d]\n", scene->amb.ratio,
		scene->amb.rgb.r, scene->amb.rgb.g, scene->amb.rgb.b);
	print_cameras(scene);
	light = scene->light;
	while (light)
	{
		printf("Light:\t\t[%.1f %.1f %.1f] [%.1f] [%d %d %d]\n",
			light->vec.x, light->vec.y, light->vec.z,
			light->ratio, light->rgb.r, light->rgb.g,
			light->rgb.b);
		light = light->next;
	}
	print_objects(scene);
}

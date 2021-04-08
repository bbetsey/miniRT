/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:26:44 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/08 21:44:09 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		free_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void		free_lights(t_scene *scene)
{
	t_light		*light;

	while (scene->light)
	{
		light = scene->light->next;
		free(scene->light);
		scene->light = light;
	}
}

void		free_obj(t_scene *scene)
{
	struct s_object	*buf;

	while (scene->objs)
	{
		buf = scene->objs->next;
		free(scene->objs->data);
		free(scene->objs);
		scene->objs = buf;
	}
}

void		free_cams(t_scene *scene)
{
	struct s_cam	*buf;

	while (scene->cams)
	{
		buf = scene->cams->next;
		free(scene->cams);
		scene->cams = buf;
	}
	if (scene->first_cam)
		free(scene->first_cam);
}

void		free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->mlx && scene->img.img)
		mlx_destroy_image(scene->mlx, scene->img.img);
	if (scene->window)
	{
		mlx_clear_window(scene->mlx, scene->window);
		mlx_destroy_window(scene->mlx, scene->window);
	}
	if (scene->objs)
		free_obj(scene);
	if (scene->cams)
		free_cams(scene);
	if (scene->light)
		free_lights(scene);
	free(scene);
}

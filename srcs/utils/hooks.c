/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:30:34 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/08 20:08:20 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			check_operator(int key_code)
{
	if (key_code == 13 || key_code == 1 || key_code == 0 ||
	key_code == 2 || key_code == 3 || key_code == 15)
		return (1);
	return (0);
}

void		next_camera(t_scene *scene)
{
	if (scene->cams->next)
	{
		scene->cams = scene->cams->next;
		draw_image(scene, 0);
	}
	else if (scene->cams != scene->first_cam)
	{
		scene->cams = scene->first_cam;
		draw_image(scene, 0);
	}
}

int			red_button(t_scene *scene)
{
	exit_minirt(scene);
	return (0);
}

void		operator(t_scene *scene, int key_code)
{
	if (key_code == 13)
		scene->cams->vec.z += 1;
	else if (key_code == 1)
		scene->cams->vec.z -= 1;
	else if (key_code == 0)
		scene->cams->vec.x -= 1;
	else if (key_code == 2)
		scene->cams->vec.x += 1;
	else if (key_code == 15)
		scene->cams->vec.y += 1;
	else if (key_code == 3)
		scene->cams->vec.y -= 1;
	draw_image(scene, 0);
}

int			ft_key(int key_code, t_scene *scene)
{
	(void)scene;
	print_command(key_code);
	if (key_code == 12)
		next_camera(scene);
	else if (check_operator(key_code))
		operator(scene, key_code);
	else if (check_dir(key_code))
		change_dir_operator(scene, key_code);
	else if (key_code == 53)
		exit_minirt(scene);
	return (0);
}

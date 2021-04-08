/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:06:30 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/08 20:30:58 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light			*light_init(t_light *light, t_scene *scene)
{
	if (!(light = malloc(sizeof(t_light))))
		error_handler("Can't allocate memory for light", scene);
	light->next = 0;
	light->check = 0;
	return (light);
}

t_light			*fill_color_l(t_light *light, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[2], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for cylinder rgb", scene);
	light->rgb.r = rt_atoi(coor[0]);
	light->rgb.g = rt_atoi(coor[1]);
	light->rgb.b = rt_atoi(coor[2]);
	free_array(coor);
	check_rgb(light->rgb, scene);
	return (light);
}

t_light			*add_light(char *line, t_scene *scene)
{
	t_light		*light;
	char		**arr;
	char		**coor;

	ft_check_line(line, scene);
	light = 0;
	light = light_init(light, scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) != 3)
		error_handler("invalid number of arguments for light", scene);
	coor = rt_split(arr[0], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for light vector", scene);
	light->vec.x = rt_atof(coor[0]);
	light->vec.y = rt_atof(coor[1]);
	light->vec.z = rt_atof(coor[2]);
	light->ratio = rt_atof(arr[1]);
	if (light->ratio > 1 || light->ratio < 0)
		error_handler("lighting ratio must be [0.0,1.0]", scene);
	free_array(coor);
	light = fill_color_l(light, arr, scene);
	light->check = 1;
	free_array(arr);
	return (light);
}

void			parse_light(char *line, t_scene *scene)
{
	t_light		*light;

	if (!scene->light)
	{
		scene->light = add_light(line, scene);
		return ;
	}
	light = scene->light;
	while (light->next)
		light = light->next;
	light->next = add_light(line, scene);
}

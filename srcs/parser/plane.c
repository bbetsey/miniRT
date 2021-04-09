/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:53:24 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 16:29:21 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*plane_init(t_object *plane, t_scene *scene)
{
	plane = malloc(sizeof(t_object));
	if (!plane)
		error_handler("Can't allocate memory for plane", scene);
	plane->type = PLANE;
	plane->data = 0;
	plane->next = 0;
	return (plane);
}

t_pl	*fill_vector_pl(t_pl *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[0], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for plane vector", scene);
	data->vec.x = rt_atof(coor[0]);
	data->vec.y = rt_atof(coor[1]);
	data->vec.z = rt_atof(coor[2]);
	free_array(coor);
	coor = rt_split(arr[1], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for plane vector", scene);
	data->n_vec.x = rt_atof(coor[0]);
	data->n_vec.y = rt_atof(coor[1]);
	data->n_vec.z = rt_atof(coor[2]);
	free_array(coor);
	check_normal(data->n_vec, scene);
	return (data);
}

t_pl	*fill_color_pl(t_pl *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[2], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for plane rgb", scene);
	data->rgb.r = rt_atoi(coor[0]);
	data->rgb.g = rt_atoi(coor[1]);
	data->rgb.b = rt_atoi(coor[2]);
	free_array(coor);
	check_rgb(data->rgb, scene);
	return (data);
}

t_object	*add_plane(char *line, t_scene *scene)
{
	char		**arr;
	t_pl		*data;
	t_object	*plane;

	plane = 0;
	plane = plane_init(plane, scene);
	ft_check_line(line, scene);
	data = malloc(sizeof(t_pl));
	if (!data)
		error_handler("Can't allocate memory for plane data", scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) != 3)
		error_handler("invalid number of arguments for plane", scene);
	data = fill_vector_pl(data, arr, scene);
	data = fill_color_pl(data, arr, scene);
	free_array(arr);
	plane->data = data;
	plane->equation = &pl_intersect;
	return (plane);
}

void	parse_plane(char *line, t_scene *scene)
{
	t_object	*obj;

	if (!scene->objs)
	{
		scene->objs = add_plane(line, scene);
		return ;
	}
	obj = scene->objs;
	while (obj->next)
		obj = obj->next;
	obj->next = add_plane(line, scene);
}

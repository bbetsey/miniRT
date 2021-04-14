/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:25:57 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/15 00:04:49 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*sphere_init(t_object *sphere, t_scene *scene)
{
	sphere = malloc(sizeof(t_object));
	if (!sphere)
		error_handler("Can't allocate memory for sphere", scene);
	sphere->data = 0;
	sphere->type = SPHERE;
	sphere->next = 0;
	return (sphere);
}

t_sp	*fill_vector_sp(t_sp *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[0], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for sphere vector", scene);
	data->vec.x = rt_atof(coor[0]);
	data->vec.y = rt_atof(coor[1]);
	data->vec.z = rt_atof(coor[2]);
	free_array(coor);
	return (data);
}

t_sp	*fill_color_sp(t_sp *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[2], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for sphere rgb", scene);
	data->rgb.r = rt_atoi(coor[0]);
	data->rgb.g = rt_atoi(coor[1]);
	data->rgb.b = rt_atoi(coor[2]);
	if (arr[3])
		data->spec = rt_atoi(arr[3]);
	free_array(coor);
	check_rgb(data->rgb, scene);
	return (data);
}

t_object	*add_sphere(char *line, t_scene *scene)
{
	t_object	*sphere;
	t_sp		*data;
	char		**arr;

	sphere = 0;
	sphere = sphere_init(sphere, scene);
	ft_check_line(line, scene);
	data = malloc(sizeof(t_sp));
	if (!data)
		error_handler("Can't allocate memory for sphere data", scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) < 3 || arr_len(arr) > 4)
		error_handler("invalid number of arguments for sphere", scene);
	data = fill_vector_sp(data, arr, scene);
	data->d = rt_atof(arr[1]);
	if (data->d < 0)
		error_handler("sphere diameter must be positive", scene);
	data = fill_color_sp(data, arr, scene);
	free_array(arr);
	sphere->data = data;
	sphere->equation = &sp_intersect;
	return (sphere);
}

void	parse_sphere(char *line, t_scene *scene)
{
	t_object	*obj;

	if (!scene->objs)
	{
		scene->objs = add_sphere(line, scene);
		return ;
	}
	obj = scene->objs;
	while (obj->next)
		obj = obj->next;
	obj->next = add_sphere(line, scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:09:47 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/15 00:31:55 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*cylinder_init(t_object *cylinder, t_scene *scene)
{
	cylinder = malloc(sizeof(t_object));
	if (!cylinder)
		error_handler("Can't allocate memory for cylinder", scene);
	cylinder->type = CYLINDER;
	cylinder->data = 0;
	cylinder->next = 0;
	return (cylinder);
}

t_cy	*fill_vector_cy(t_cy *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[0], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for cylinder vector", scene);
	data->vec.x = rt_atof(coor[0]);
	data->vec.y = rt_atof(coor[1]);
	data->vec.z = rt_atof(coor[2]);
	free_array(coor);
	coor = rt_split(arr[1], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for cylinder vector", scene);
	data->n_vec.x = rt_atof(coor[0]);
	data->n_vec.y = rt_atof(coor[1]);
	data->n_vec.z = rt_atof(coor[2]);
	free_array(coor);
	check_normal(data->n_vec, scene);
	return (data);
}

t_cy	*fill_color_cy(t_cy *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[4], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for cylinder rgb", scene);
	data->rgb.r = rt_atoi(coor[0]);
	data->rgb.g = rt_atoi(coor[1]);
	data->rgb.b = rt_atoi(coor[2]);
	if (arr[5])
		data->spec = rt_atoi(arr[5]);
	else
		data->spec = SPECULAR;
	free_array(coor);
	check_rgb(data->rgb, scene);
	return (data);
}

t_object	*add_cylinder(char *line, t_scene *scene)
{
	t_object	*cylinder;
	t_cy		*data;
	char		**arr;

	cylinder = 0;
	cylinder = cylinder_init(cylinder, scene);
	ft_check_line(line, scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) < 5 || arr_len(arr) > 6)
		error_handler("invalid number of arguments for cylinder", scene);
	data = malloc(sizeof(t_cy));
	if (!data)
		error_handler("Can't allocate memory for cylinder data", scene);
	data = fill_vector_cy(data, arr, scene);
	data->d = rt_atof(arr[2]);
	data->h = rt_atof(arr[3]);
	if (data->d < 0 || data->h < 0)
		error_handler("cylinder diameter or height must be positive", scene);
	data = fill_color_cy(data, arr, scene);
	data->n_vec = vec_norm(data->n_vec);
	free_array(arr);
	cylinder->data = data;
	cylinder->equation = &cy_intersect;
	return (cylinder);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	t_object	*obj;

	if (!scene->objs)
	{
		scene->objs = add_cylinder(line, scene);
		return ;
	}
	obj = scene->objs;
	while (obj->next)
		obj = obj->next;
	obj->next = add_cylinder(line, scene);
}

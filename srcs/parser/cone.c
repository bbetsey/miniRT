/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:38:25 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/16 15:04:55 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*cone_init(t_object *cone, t_scene *scene)
{
	cone = malloc(sizeof(t_object));
	if (!cone)
		error_handler("Can't allocate memory for cone", scene);
	cone->type = CYLINDER;
	cone->data = 0;
	cone->next = 0;
	return (cone);
}

t_co	*fill_vector_co(t_co *data, char **arr, t_scene *scene)
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

t_co	*fill_color_co(t_co *data, char **arr, t_scene *scene)
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
	if (arr[5] && arr[6])
		data->ref = rt_atof(arr[6]);
	else
		data->ref = 0;
	free_array(coor);
	check_rgb(data->rgb, scene);
	return (data);
}

t_object	*add_cone(char *line, t_scene *scene)
{
	t_object	*cone;
	t_co		*data;
	char		**arr;

	cone = 0;
	cone = cone_init(cone, scene);
	ft_check_line(line, scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) < 5 || arr_len(arr) > 7)
		error_handler("invalid number of arguments for cone", scene);
	data = malloc(sizeof(t_cy));
	if (!data)
		error_handler("Can't allocate memory for cylinder data", scene);
	data = fill_vector_co(data, arr, scene);
	data->d = rt_atof(arr[2]);
	data->h = rt_atof(arr[3]);
	if (data->d < 0 || data->h < 0)
		error_handler("cylinder diameter or height must be positive", scene);
	data = fill_color_co(data, arr, scene);
	data->n_vec = vec_norm(data->n_vec);
	free_array(arr);
	cone->data = data;
	cone->equation = &co_intersect;
	return (cone);
}

void	parse_cone(char *line, t_scene *scene)
{
	t_object	*obj;

	if (!scene->objs)
	{
		scene->objs = add_cone(line, scene);
		return ;
	}
	obj = scene->objs;
	while (obj->next)
		obj = obj->next;
	obj->next = add_cone(line, scene);
}

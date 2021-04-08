/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:40:58 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/07 12:25:30 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*triangle_init(t_object *triangle, t_scene *scene)
{
	if (!(triangle = malloc(sizeof(t_object))))
		error_handler("Can't allocate memory for triangle", scene);
	triangle->type = TRIANGLE;
	triangle->data = 0;
	triangle->next = 0;
	return (triangle);
}

t_tr		*fill_vector_tr(t_tr *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[0], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for square vector 1", scene);
	data->v1.x = rt_atof(coor[0]);
	data->v1.y = rt_atof(coor[1]);
	data->v1.z = rt_atof(coor[2]);
	free_array(coor);
	coor = rt_split(arr[1], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for square vector 2", scene);
	data->v2.y = rt_atof(coor[1]);
	data->v2.x = rt_atof(coor[0]);
	data->v2.z = rt_atof(coor[2]);
	free_array(coor);
	coor = rt_split(arr[2], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for square vector 3", scene);
	data->v3.y = rt_atof(coor[1]);
	data->v3.x = rt_atof(coor[0]);
	data->v3.z = rt_atof(coor[2]);
	free_array(coor);
	return (data);
}

t_tr		*fill_color_tr(t_tr *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[3], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for square rgb", scene);
	data->rgb.r = rt_atoi(coor[0]);
	data->rgb.g = rt_atoi(coor[1]);
	data->rgb.b = rt_atoi(coor[2]);
	free_array(coor);
	check_rgb(data->rgb, scene);
	return (data);
}

t_object	*add_triangle(char *line, t_scene *scene)
{
	t_object	*triangle;
	t_tr		*data;
	char		**arr;

	triangle = 0;
	triangle = triangle_init(triangle, scene);
	ft_check_line(line, scene);
	if (!(data = malloc(sizeof(t_tr))))
		error_handler("Can't allocate memory for triangle data", scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) != 4)
		error_handler("invalid number of arguments for triangle", scene);
	data = fill_vector_tr(data, arr, scene);
	data = fill_color_tr(data, arr, scene);
	free_array(arr);
	data->norm = vec_norm(vec_cross(vec_sub(data->v2, data->v1),
	vec_sub(data->v3, data->v1)));
	triangle->data = data;
	triangle->equation = &tr_intersect;
	return (triangle);
}

void		parse_triangle(char *line, t_scene *scene)
{
	t_object	*obj;

	if (!scene->objs)
	{
		scene->objs = add_triangle(line, scene);
		return ;
	}
	obj = scene->objs;
	while (obj->next)
		obj = obj->next;
	obj->next = add_triangle(line, scene);
}

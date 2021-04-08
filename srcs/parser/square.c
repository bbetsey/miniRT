/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:31:39 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/07 12:25:38 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*square_init(t_object *square, t_scene *scene)
{
	if (!(square = malloc(sizeof(t_object))))
		error_handler("Can't allocate memory for square", scene);
	square->type = SQUARE;
	square->data = 0;
	square->next = 0;
	return (square);
}

t_sq		*fill_vector_sq(t_sq *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[0], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for square vector", scene);
	data->vec.x = rt_atof(coor[0]);
	data->vec.y = rt_atof(coor[1]);
	data->vec.z = rt_atof(coor[2]);
	free_array(coor);
	coor = rt_split(arr[1], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for square vector", scene);
	data->n_vec.x = rt_atof(coor[0]);
	data->n_vec.y = rt_atof(coor[1]);
	data->n_vec.z = rt_atof(coor[2]);
	free_array(coor);
	check_normal(data->n_vec, scene);
	return (data);
}

t_sq		*fill_color_sq(t_sq *data, char **arr, t_scene *scene)
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

t_object	*add_square(char *line, t_scene *scene)
{
	t_object	*square;
	t_sq		*data;
	char		**arr;

	square = 0;
	square = square_init(square, scene);
	ft_check_line(line, scene);
	if (!(data = malloc(sizeof(t_sq))))
		error_handler("Can't allocate memory for square data", scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) != 4)
		error_handler("invalid number of arguments for square", scene);
	data = fill_vector_sq(data, arr, scene);
	if ((data->side = rt_atof(arr[2])) < 0)
		error_handler("square side size must be positive", scene);
	data = fill_color_sq(data, arr, scene);
	free_array(arr);
	square->data = data;
	square->equation = &sq_intersect;
	return (square);
}

void		parse_square(char *line, t_scene *scene)
{
	t_object	*obj;

	if (!scene->objs)
	{
		scene->objs = add_square(line, scene);
		return ;
	}
	obj = scene->objs;
	while (obj->next)
		obj = obj->next;
	obj->next = add_square(line, scene);
}

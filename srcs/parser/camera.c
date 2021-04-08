/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:52:24 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/07 12:27:05 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam		*cams_init(t_cam *cams)
{
	cams->next = 0;
	return (cams);
}

t_cam		*fill_vector_cam(t_cam *data, char **arr, t_scene *scene)
{
	char		**coor;

	coor = rt_split(arr[0], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for camera vector", scene);
	data->vec.x = rt_atof(coor[0]);
	data->vec.y = rt_atof(coor[1]);
	data->vec.z = rt_atof(coor[2]);
	free_array(coor);
	coor = rt_split(arr[1], ",,");
	if (arr_len(coor) != 3)
		error_handler("invalid number of arguments for camera vector", scene);
	data->n_vec.x = rt_atof(coor[0]);
	data->n_vec.y = rt_atof(coor[1]);
	data->n_vec.z = rt_atof(coor[2]);
	free_array(coor);
	check_normal(data->n_vec, scene);
	return (data);
}

t_cam		*add_camera(char *line, t_scene *scene)
{
	char	**arr;
	t_cam	*cam;

	ft_check_line(line, scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) != 3)
		error_handler("invalid number of arguments for camera", scene);
	if (!(cam = malloc(sizeof(t_cam))))
		error_handler("Can't allocate memory for camera", scene);
	cam = cams_init(cam);
	cam = fill_vector_cam(cam, arr, scene);
	cam->fov = rt_atof(arr[2]);
	if (cam->fov < 0 || cam->fov > 180)
		error_handler("the camera fov must be [0;180]", scene);
	free_array(arr);
	return (cam);
}

void		parse_camera(char *line, t_scene *scene)
{
	t_cam	*cams;

	if (!scene->cams)
	{
		scene->cams = add_camera(line, scene);
		return ;
	}
	cams = scene->cams;
	while (cams->next)
		cams = cams->next;
	cams->next = add_camera(line, scene);
}

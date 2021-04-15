/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:32:30 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/15 20:53:28 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	wait_threads(pthread_t *threads, int height)
{
	int		i;

	i = 0;
	while (i < height)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	*run_thread(void *thread_data)
{
	t_thr_data	*data;
	t_ray		ray;

	data = (t_thr_data *)thread_data;
	ray.eye = data->scene->cams->vec;
	while (data->x_start < data->x_end)
	{
		ray.dir = make_ray(data->x_start, data->y, data->scene->cams);
		data->colors[data->i] = intersect(data->scene, ray,
				(t_limit){1, INFINITY}, RECURSIVE);
		data->x_start++;
		data->i++;
	}
	return (SUCCESS);
}

void	init_thread_data(t_scene *scene, t_thr_data *data, pthread_t *threads)
{
	int		height;
	double	y;

	height = 0;
	y = scene->y_start;
	while (height < scene->res.height)
	{
		data[height].j = height;
		data[height].i = 0;
		data[height].x_start = scene->x_start;
		data[height].x_end = scene->x_end;
		data[height].y = y;
		data[height].colors = malloc(sizeof(t_color) * scene->res.width);
		if (!data[height].colors)
			error_handler("Can't allocate memory for colors", scene);
		data[height].colors = ft_bzero(data[height].colors, scene->res.width);
		data[height].scene = scene;
		pthread_create(&(threads[height]), NULL, run_thread, &(data[height]));
		height++;
		y--;
	}
}

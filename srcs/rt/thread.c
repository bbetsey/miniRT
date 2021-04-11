/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:32:30 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/11 00:44:15 by bbetsey          ###   ########.fr       */
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
	t_vector	ray;

	data = (t_thr_data *)thread_data;
	while (data->x_start < data->x_end)
	{
		ray = make_ray(data->x_start, data->y, data->scene->cams);
		data->colors[data->i] = intersect(data->scene, ray);
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
	while (y > scene->y_end)
	{
		data[height].j = height;
		data[height].i = 0;
		data[height].x_start = scene->x_start;
		data[height].x_end = scene->x_end;
		data[height].y = y;
		data[height].colors = malloc(sizeof(int) * scene->res.width);
		data[height].colors = ft_bzero(data[height].colors, scene->res.width);
		data[height].scene = scene;
		pthread_create(&(threads[height]), NULL, run_thread, &(data[height]));
		height++;
		y--;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:32:30 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/12 01:31:33 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_color_matrix(t_aa_matrix m)
{
	int		average;

	average = (m.a1 + m.a2 + m.a3 + m.b1 + m.b2 + m.b3 + m.c1 + m.c2 + m.c3) / 9;
	if (abs(average - m.b2) > 100000)
		return (average);
	return (m.b2);
}

void	anti_aliasing(t_thr_data *data, int height, int width)
{
	t_aa_matrix		matrix;
	int				i;
	int				j;

	j = 1;
	while (j < (height - 1))
	{
		i = 1;
		while (i < (width - 1))
		{
			matrix.a1 = data[j - 1].colors[i - 1];
			matrix.a2 = data[j - 1].colors[i];
			matrix.a3 = data[j - 1].colors[i + 1];
			matrix.b1 = data[j].colors[i - 1];
			matrix.b2 = data[j].colors[i];
			matrix.b3 = data[j].colors[i + 1];
			matrix.c1 = data[j + 1].colors[i - 1];
			matrix.c2 = data[j + 1].colors[i];
			matrix.c3 = data[j + 1].colors[i + 1];
			data[j].colors[i] = check_color_matrix(matrix);
			i++;
		}
		j++;
	}
}

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
		if (!data[height].colors)
			error_handler("Can't allocate memory for colors", scene);
		data[height].scene = scene;
		pthread_create(&(threads[height]), NULL, run_thread, &(data[height]));
		height++;
		y--;
	}
}

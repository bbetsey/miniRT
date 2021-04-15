/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:34:00 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/15 15:28:16 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	additional_ray_tracing(t_scene *scene, int i, int j)
{
	double		x;
	double		y;
	t_vector	ray;
	t_color		color;

	y = scene->y_start - j;
	x = scene->x_start + i;
	j = 0;
	color = (t_color){0, 0, 0};
	while (j < PIXEL_DIV)
	{
		i = 0;
		while (i < PIXEL_DIV)
		{
			ray = make_ray(x + ((1.0 / (2.0 * (double)PIXEL_DIV))
						+ ((double)i / (double)PIXEL_DIV)),
					y - ((1.0 / (2.0 * (double)PIXEL_DIV))
						+ ((double)j / (double)PIXEL_DIV)), scene->cams);
			color = color_sum(color, intersect(scene, ray, (t_limit){1, INFINITY}, RECURSIVE));
			i++;
		}
		j++;
	}
	return (color_div(color, pow(PIXEL_DIV, 2)));
}

t_color	check_color_matrix(t_aa_matrix m, t_scene *scene, int i, int j)
{
	t_color		average;

	average = color_sum(color_sum(color_sum(color_sum(color_sum(color_sum
							(color_sum(color_sum(m.a1, m.a2), m.a3),
								m.b1), m.b2), m.b3), m.c1), m.c2), m.c3);
	average = color_div(average, 9.0);
	if (abs(average.r - m.b2.r) > DIFF || abs(average.g - m.b2.g) > DIFF
		|| abs(average.b - m.b2.b) > DIFF)
		return (additional_ray_tracing(scene, i, j));
	return (m.b2);
}

void	*run_aa_thread(void *thread_data)	
{
	t_aa_thr_data	*aa_data;
	t_aa_matrix		matrix;
	int				i;
	int				j;

	aa_data = (t_aa_thr_data *)thread_data;
	j = aa_data->j;
	i = 1;
	while (i < (aa_data->width - 1))
	{
		matrix.a1 = aa_data->data[j - 1].colors[i - 1];
		matrix.a2 = aa_data->data[j - 1].colors[i];
		matrix.a3 = aa_data->data[j - 1].colors[i + 1];
		matrix.b1 = aa_data->data[j].colors[i - 1];
		matrix.b2 = aa_data->data[j].colors[i];
		matrix.b3 = aa_data->data[j].colors[i + 1];
		matrix.c1 = aa_data->data[j + 1].colors[i - 1];
		matrix.c2 = aa_data->data[j + 1].colors[i];
		matrix.c3 = aa_data->data[j + 1].colors[i + 1];
		aa_data->data[j].colors[i] = check_color_matrix(matrix,
				aa_data->data->scene, i, j);
		i++;
	}
	return (SUCCESS);
}

void	anti_aliasing(t_thr_data *data, int width, int height)	
{
	t_aa_thr_data	*aa_data;
	pthread_t		*threads;
	int				i;
	int				j;

	j = 1;
	aa_data = malloc(sizeof(t_aa_thr_data) * (height - 1));
	threads = malloc(sizeof(pthread_t) * (height - 1));
	if (!aa_data || !threads)
		error_handler("Can't allocate memory for threads or aa_data",
			data->scene);
	i = 0;
	while (j < (height - 1))
	{
		aa_data[i].width = width;
		aa_data[i].j = j;
		aa_data[i].data = data;
		pthread_create(&(threads[i]), NULL, run_aa_thread, &(aa_data[i]));
		j++;
		i++;
	}
	wait_threads(threads, height - 1);
	free(threads);
}

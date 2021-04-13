/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:28:41 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/12 01:26:29 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	install_cams(t_scene *scene)
{
	t_cam	*cams;

	cams = scene->cams;
	scene->res.ratio = (float)scene->res.width / (float)scene->res.height;
	while (cams)
	{
		cams->v_width = (double)tan(cams->fov / 2.0 * (M_PI / 180)) * 2.0;
		cams->v_height = (double)cams->v_width / scene->res.ratio;
		cams->x_pixel = (double)cams->v_width / scene->res.width;
		cams->y_pixel = (double)cams->v_height / scene->res.height;
		cams = cams->next;
	}
}

void	pixel_put(t_thr_data *data, t_scene *scene)
{
	int		x;
	int		y;

	y = 0;
	while (y < scene->res.height)
	{
		x = 0;
		while (x < scene->res.width)
		{
			my_mlx_pixel_put(&scene->img, x, y, data[y].colors[x]);
			x++;
		}
		if (data[y].colors)
			free(data[y].colors);
		y++;
	}
}

void	trace_ray(t_scene *scene)
{
	t_thr_data	*data;
	pthread_t	*threads;

	data = malloc(sizeof(t_thr_data) * scene->res.height);
	threads = malloc(sizeof(pthread_t) * scene->res.height);
	if (!data || !threads)
		error_handler("Can't allocate memory for threads or data", scene);
	data = ft_bzero(data, scene->res.height);
	init_thread_data(scene, data, threads);
	wait_threads(threads, scene->res.height);
	pixel_put(data, scene);
	if (threads)
		free(threads);
	if (data)
		free(data);
}

void	draw_image(t_scene *scene, int is_save)
{
	trace_ray(scene);
	if (is_save)
		create_image(scene);
	else
		mlx_put_image_to_window(scene->mlx, scene->window,
			scene->img.img, 0, 0);
}

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
	int			x;
	int			y;
	int			color;

	y = 0;
	while (y < scene->res.height)
	{
		x = 0;
		while (x < scene->res.width)
		{
			color = create_trgb(0, data[y].colors[x].r,
					data[y].colors[x].g, data[y].colors[x].b);
			my_mlx_pixel_put(&scene->img, x, y, color);
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
	anti_aliasing(data, scene->res.width, scene->res.height);
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

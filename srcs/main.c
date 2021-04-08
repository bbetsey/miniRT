/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:23:47 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/08 21:41:05 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		install_window(t_scene *scene)
{
	if (!(scene->window = mlx_new_window(scene->mlx,
	scene->res.width, scene->res.height, "miniRT")))
		error_handler("can't install mlx window", scene);
	scene->img.img = mlx_new_image(scene->mlx, scene->res.width,
	scene->res.height);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
	&scene->img.bits_per_pixel, &scene->img.line_length,
	&scene->img.endian);
}

void		start_ray_tracing(t_scene *scene)
{
	if (!(scene->mlx = mlx_init()))
		error_handler("can't init mlx", scene);
	install_window(scene);
	install_cams(scene);
	mlx_key_hook(scene->window, ft_key, scene);
	draw_image(scene, 0);
	mlx_hook(scene->window, 17, 1L << 17, red_button, scene);
	mlx_loop(scene->mlx);
}

void		check_resolution(t_scene *scene)
{
	int		sizex;
	int		sizey;

	mlx_get_screen_size(scene->mlx, &sizex, &sizey);
	if (scene->res.width > sizex)
	{
		printf(BOLDYELLOW "Too large reolution width." RESET
		" New width: %d\n", sizex);
		scene->res.width = sizex;
	}
	if (scene->res.height > sizey)
	{
		printf(BOLDYELLOW "Too large reolution height." RESET
		" New height: %d\n", sizey);
		scene->res.height = sizey;
	}
}

int			main(int argc, char **argv)
{
	t_scene		*scene;

	scene = 0;
	if (argc < 2 || argc > 3)
		error_handler("wrong number of arguments for miniRT", scene);
	else if (argc == 3)
	{
		if (!rt_strcmp(argv[2], "--save"))
			save_image(scene, argv[1]);
		error_handler("Unknown argument", scene);
	}
	read_and_parse_file(argv[1], &scene);
	scene->first_cam = scene->cams;
	check_resolution(scene);
	start_ray_tracing(scene);
	free_scene(scene);
	return (0);
}

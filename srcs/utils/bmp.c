/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 20:38:57 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/13 18:27:06 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_bmp(char **data, t_scene *scene)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 120;
	y = scene->res.height;
	while (y--)
	{
		x = -1;
		while (++x < scene->res.width)
		{
			j = (x * (scene->img.bits_per_pixel / 8))
				+ (y * scene->img.line_length);
			*(*data + i++) = *(scene->img.addr + j++);
			*(*data + i++) = *(scene->img.addr + j++);
			*(*data + i++) = *(scene->img.addr + j);
		}
	}
}

void	write_header_bmp(char **data, t_scene *scene)
{
	unsigned int	size;

	size = scene->res.height * scene->res.width * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + 120);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = 120;
	*(unsigned int *)(*data + 14) = 120 - 14;
	*(unsigned int *)(*data + 18) = scene->res.width;
	*(unsigned int *)(*data + 22) = scene->res.height;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void	create_image(t_scene *scene)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = scene->res.height * scene->res.width * 3;
	data = malloc(size + 120);
	if (!data)
		error_handler("Can't allocate memory", scene);
	i = 0;
	while (i < size + 120)
		data[i++] = 0;
	write_header_bmp(&data, scene);
	create_bmp(&data, scene);
	fd = open("img.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd <= 0)
		error_handler("Can't open file", scene);
	write(fd, data, (size + 120));
	close(fd);
}

void	save_image(t_scene *scene, char *filename)
{
	read_and_parse_file(filename, &scene);
	scene->first_cam = scene->cams;
	scene->mlx = mlx_init();
	if (!scene->mlx)
		error_handler("can't init mlx", scene);
	install_window(scene);
	install_cams(scene);
	draw_image(scene, 1);
	printf(BOLDGREEN "Success! Created image: image.bmp\n" RESET);
	exit_minirt(scene);
}

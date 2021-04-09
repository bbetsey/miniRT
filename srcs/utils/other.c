/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:22:06 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 15:34:38 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}

void	print_command(int key_code)
{
	if (key_code == 13)
		write(1, "Move Forward\n", 13);
	else if (key_code == 1)
		write(1, "Move Back\n", 10);
	else if (key_code == 0)
		write(1, "Move Left\n", 10);
	else if (key_code == 2)
		write(1, "Move Right\n", 11);
	else if (key_code == 15)
		write(1, "Move Up\n", 8);
	else if (key_code == 3)
		write(1, "Move Down\n", 10);
	else if (key_code == 12)
		write(1, "Change Camera\n", 14);
	else if (key_code == 126)
		write(1, "Up Camera\n", 10);
	else if (key_code == 125)
		write(1, "Down Camera\n", 12);
	else if (key_code == 124)
		write(1, "Right Camera\n", 13);
	else if (key_code == 123)
		write(1, "Left Camera\n", 12);
}

int	check_dir(int key_code)
{
	if (key_code == 123 || key_code == 124 || key_code == 125
		|| key_code == 126)
		return (1);
	return (0);
}

void	change_dir_operator(t_scene *scene, int key_code)
{
	if (key_code == 126)
	{
		scene->cams->n_vec.y += 0.3;
		scene->cams->n_vec.z -= 0.3;
	}
	else if (key_code == 125)
	{
		scene->cams->n_vec.z += 0.3;
		scene->cams->n_vec.y -= 0.3;
	}
	else if (key_code == 123)
	{
		scene->cams->n_vec.z -= 0.3;
		scene->cams->n_vec.x -= 0.3;
	}
	else if (key_code == 124)
	{
		scene->cams->n_vec.z += 0.3;
		scene->cams->n_vec.x += 0.3;
	}
	draw_image(scene, 0);
}

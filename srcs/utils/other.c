/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:22:06 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/11 16:41:18 by bbetsey          ###   ########.fr       */
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
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Move Forward\n" RESET, 40);
	else if (key_code == 1)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Move Back\n" RESET, 37);
	else if (key_code == 0)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Move Left\n" RESET, 37);
	else if (key_code == 2)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Move Right\n" RESET, 38);
	else if (key_code == 15)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Move Up\n" RESET, 35);
	else if (key_code == 3)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Move Down\n" RESET, 37);
	else if (key_code == 12)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Change Cam\n" RESET, 39);
	else if (key_code == 126)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Turn Up\n" RESET, 36);
	else if (key_code == 125)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Turn Down\n" RESET, 38);
	else if (key_code == 124)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Turn Right\n" RESET, 39);
	else if (key_code == 123)
		write(1, BOLDWHITE "Tap: " RESET BOLDMAGENTA "Turn Left\n" RESET, 38);
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
		scene->cams->n_vec = vec_norm(vec_rotate_x(scene->cams->n_vec, 10));
	else if (key_code == 125)
		scene->cams->n_vec = vec_norm(vec_rotate_x(scene->cams->n_vec, -10));
	else if (key_code == 123)
		scene->cams->n_vec = vec_norm(vec_rotate_y(scene->cams->n_vec, 10));
	else if (key_code == 124)
		scene->cams->n_vec = vec_norm(vec_rotate_y(scene->cams->n_vec, -10));
	draw_image(scene, 0);
}

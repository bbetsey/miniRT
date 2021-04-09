/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:30:52 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 16:22:08 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char *line, t_scene *scene)
{
	char	**arr;
	char	**rgb;

	ft_check_line(line, scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) != 2)
		error_handler("invalid number of arguments for ambient", scene);
	scene->amb.ratio = rt_atof(arr[0]);
	if (scene->amb.ratio > 1 || scene->amb.ratio < 0)
		error_handler("ambient lighting ratio must be [0.0,1.0]", scene);
	rgb = rt_split(arr[1], ",,");
	if (arr_len(rgb) != 3)
		error_handler("invalid number of arguments for ambient rgb", scene);
	scene->amb.rgb.r = rt_atoi(rgb[0]);
	scene->amb.rgb.g = rt_atoi(rgb[1]);
	scene->amb.rgb.b = rt_atoi(rgb[2]);
	scene->amb.check = 1;
	free_array(arr);
	free_array(rgb);
}

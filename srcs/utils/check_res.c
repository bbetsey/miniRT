/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:59:34 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 17:05:57 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_resolution(t_scene *scene)
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

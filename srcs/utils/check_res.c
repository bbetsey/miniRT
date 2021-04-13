/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:59:34 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/13 18:26:25 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_resolution(t_scene *scene)
{
	int		sizex;
	int		sizey;

	mlx_get_screen_size(&sizex, &sizey);
	if (scene->res.width > sizex)
	{
		scene->res.width = sizex;
		printf(BOLDYELLOW "Too large reolution width." RESET
			" New width: %d\n", scene->res.width);
	}
	if (scene->res.height > sizey)
	{
		scene->res.height = sizey;
		printf(BOLDYELLOW "Too large reolution height." RESET
			" New height: %d\n", scene->res.height);
	}
}

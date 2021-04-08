/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:26:49 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/08 17:29:57 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		error_handler(char *str, t_scene *scene)
{
	printf(BOLDRED "\nError » " RESET);
	printf(BOLDWHITE "%s" RESET "\n\n", str);
	free_scene(scene);
	exit(FAILURE);
}

void		exit_minirt(t_scene *scene)
{
	free(scene);
	printf(BOLDGREEN "*** Free Scene ✔︎ GoodBye!! ***\n" RESET);
	exit(SUCCESS);
}

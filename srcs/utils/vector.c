/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:26:54 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 15:27:28 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	new_vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

float	vec_len(t_vector vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

float	vec_dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	vec_multi(t_vector vec, double n)
{
	return (new_vector(vec.x * n, vec.y * n, vec.z * n));
}

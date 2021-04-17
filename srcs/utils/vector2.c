#include "minirt.h"

t_vector	vec_cross(t_vector v1, t_vector v2)
{
	t_vector	vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_vector	vec_norm(t_vector vec)
{
	double	length;

	length = vec_len(vec);
	vec.x /= length;
	vec.y /= length;
	vec.z /= length;
	return (vec);
}

t_vector	vec_sum(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vector	vec_rotate_y(t_vector vec, int angle)
{
	t_vector	res;

	res.x = vec.x * cos(angle * M_PI / 180) - vec.z * sin(angle * M_PI / 180);
	res.z = vec.x * sin(angle * M_PI / 180) + vec.z * cos(angle * M_PI / 180);
	res.y = vec.y;
	return (res);
}

t_vector	vec_rotate_x(t_vector vec, int angle)
{
	t_vector	res;

	res.z = vec.z * cos(angle * M_PI / 180) - vec.y * sin(angle * M_PI / 180);
	res.y = vec.z * sin(angle * M_PI / 180) + vec.y * cos(angle * M_PI / 180);
	res.x = vec.x;
	return (res);
}

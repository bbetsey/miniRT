#include "minirt.h"

t_vector	rotate_normal(t_vector dir, t_vector norm)
{
	double		tmp;

	tmp = vec_dot(dir, norm);
	if (tmp < 0)
		return (vec_norm(norm));
	return (vec_multi(vec_norm(norm), -1.0));
}

t_vector	multi_matrix(t_vector vec, t_matrix mtrx)
{
	t_vector	result;

	result.x = vec.x * mtrx.right.x + vec.y * mtrx.up.x + vec.z
		* mtrx.forward.x + mtrx.origin.x;
	result.y = vec.x * mtrx.right.y + vec.y * mtrx.up.y + vec.z
		* mtrx.forward.y + mtrx.origin.y;
	result.z = vec.x * mtrx.right.z + vec.y * mtrx.up.z + vec.z
		* mtrx.forward.z + mtrx.origin.z;
	return (result);
}

t_matrix	look_at(t_vector eye, t_vector dir)
{
	t_matrix	mtrx;
	t_vector	tmp;

	mtrx.forward = dir;
	mtrx.origin = eye;
	if (dir.x == 0 && dir.y == 1 && dir.z == 0)
		tmp = new_vector(0, 0, -1);
	else if (dir.x == 0 && dir.y == -1 && dir.z == 0)
		tmp = new_vector(0, 0, 1);
	else
		tmp = new_vector(0, 1, 0);
	mtrx.right = vec_norm(vec_cross(tmp, mtrx.forward));
	mtrx.up = vec_norm(vec_cross(mtrx.forward, mtrx.right));
	return (mtrx);
}

t_vector	make_ray(double x, double y, t_cam *cam)
{
	t_matrix	mtrx;
	t_vector	dir;

	mtrx = look_at(cam->vec, vec_norm(cam->n_vec));
	dir = new_vector(cam->x_pixel * (x + 0.5), cam->y_pixel * (y + 0.5), 1);
	dir = multi_matrix(dir, mtrx);
	dir = vec_norm(vec_sub(dir, cam->vec));
	return (dir);
}

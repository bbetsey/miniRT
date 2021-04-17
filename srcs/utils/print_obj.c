#include "minirt.h"

void	print_plane(t_object *plane)
{
	t_pl		*data;

	data = plane->data;
	printf("Plane:\t\t[%.1f %.1f %.1f] [%.1f %.1f %.1f] [%d %d %d] [%d]\n",
		data->vec.x, data->vec.y, data->vec.z, data->n_vec.x,
		data->n_vec.y, data->n_vec.z, data->rgb.r, data->rgb.g, data->rgb.b,
		data->spec);
}

void	print_sphere(t_object *sphere)
{
	t_sp		*data;

	data = sphere->data;
	printf("Sphere:\t\t[%.1f %.1f %.1f] [%.1f] [%d %d %d] [%d]\n",
		data->vec.x, data->vec.y, data->vec.z, data->d,
		data->rgb.r, data->rgb.g, data->rgb.b, data->spec);
}

void	print_cylinder(t_object *cylinder)
{
	t_cy		*data;

	data = cylinder->data;
	printf("Cylinder:\t[%.1f %.1f %.1f] [%.1f %.1f %.1f] [%.1f] "
		"[%.1f] [%d %d %d] [%d]\n",
		data->vec.x, data->vec.y, data->vec.z, data->n_vec.x, data->n_vec.y,
		data->n_vec.z, data->d, data->h, data->rgb.r, data->rgb.g, data->rgb.b,
		data->spec);
}

void	print_triangle(t_object *triangle)
{
	t_tr		*data;

	data = triangle->data;
	printf("Triangle:\t[%.1f %.1f %.1f] [%.1f %.1f %.1f] "
		"[%.1f %.1f %.1f] [%d %d %d] [%d] [%.1f]\n",
		data->v1.x, data->v1.y, data->v1.z, data->v2.x, data->v2.y,
		data->v2.z, data->v3.x, data->v3.y, data->v3.z, data->rgb.r,
		data->rgb.g, data->rgb.b, data->spec, data->ref);
}

void	print_square(t_object *square)
{
	t_sq		*data;

	data = square->data;
	printf("Square:\t\t[%.1f %.1f %.1f] [%.1f %.1f %.1f] [%.1f] "
		"[%d %d %d]\n",
		data->vec.x, data->vec.y, data->vec.z, data->n_vec.x, data->n_vec.y,
		data->n_vec.z, data->side, data->rgb.r, data->rgb.g, data->rgb.b);
}

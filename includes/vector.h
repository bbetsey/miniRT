#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

t_vector			new_vector(double x, double y, double z);
t_vector			vec_sub(t_vector v1, t_vector v2);
t_vector			vec_cross(t_vector v1, t_vector v2);
float				vec_len(t_vector vec);
float				vec_dot(t_vector v1, t_vector v2);
t_vector			vec_norm(t_vector vec);
t_vector			vec_multi(t_vector vec, double n);
t_vector			vec_sum(t_vector v1, t_vector v2);

#endif

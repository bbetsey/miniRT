/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:28:14 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/15 15:19:51 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

typedef struct s_tmp
{
	t_vector	ray;
	t_vector	n;
}				t_tmp;

typedef struct s_trace
{
	double		x;
	double		y;
	int			i;
	int			j;
	float		x_aim;
	float		y_aim;
	int			color;
	int			buf_clr;
}					t_trace;

typedef struct s_quadro
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		x1;
	double		x2;
}					t_quadro;

typedef struct s_sq_eq
{
	double		a;
	double		b;
	double		x1;
	double		x2;
	t_vector	vec;
}					t_sq_eq;

typedef struct s_cy_eq
{
	t_vector	sub;
	double		a;
	double		b;
	double		c;
	double		d;
	double		x1;
	double		x2;
	double		z1;
	double		z2;
}					t_cy_eq;

typedef struct s_specular
{
	t_vector	n;
	t_vector	l;
	t_vector	ray;
	float		rat;
	int			spec;
}				t_specular;

typedef struct s_matrix
{
	t_vector	up;
	t_vector	right;
	t_vector	forward;
	t_vector	origin;
}					t_matrix;

typedef struct s_thr_data
{
	int			j;
	int			i;
	double		y;
	double		x_start;
	double		x_end;
	t_color		*colors;
	t_scene		*scene;
}				t_thr_data;

typedef struct s_aa_matrix
{
	t_color		a1;
	t_color		a2;
	t_color		a3;
	t_color		b1;
	t_color		b2;
	t_color		b3;
	t_color		c1;
	t_color		c2;
	t_color		c3;
}				t_aa_matrix;

typedef struct s_aa_thr_data
{
	int			width;
	int			j;
	t_thr_data	*data;
}				t_aa_thr_data;

void			trace_ray(t_scene *scene);
t_color			intersect(t_scene *scene, t_vector ray, t_limit lim,
					int recursive);
void			install_cams(t_scene *scene);
t_closest		sp_intersect(void *data, t_vector eye, t_vector dir,
					t_limit lim);
t_closest		pl_intersect(void *data, t_vector eye, t_vector dir,
					t_limit lim);
t_closest		tr_intersect(void *data, t_vector eye, t_vector dir,
					t_limit lim);
t_closest		sq_intersect(void *data, t_vector eye, t_vector dir,
					t_limit lim);
t_closest		cy_intersect(void *data, t_vector eye, t_vector dir,
					t_limit lim);
float			lightning(t_scene *scene);
float			make_specular(t_specular spec);
float			light_point(t_vector n, t_vector l, float ratio);
float			compute_lightning(t_scene *scene, t_light *light,
					t_closest solution, t_tmp tmp);
t_color			compute_color(t_closest closest, t_scene *scene, t_vector ray);
void			draw_image(t_scene *scene, int is_save);
void			init_thread_data(t_scene *scene, t_thr_data *data,
					pthread_t *threads);
void			*run_thread(void *thread_data);
void			wait_threads(pthread_t *threads, int height);
void			anti_aliasing(t_thr_data *data, int height, int width);
void			wait_threads(pthread_t *threads, int height);
t_vector		reflect_ray(t_vector r, t_vector n);

#endif

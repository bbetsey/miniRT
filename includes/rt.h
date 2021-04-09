/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:28:14 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 16:35:51 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

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

typedef struct s_matrix
{
	t_vector	up;
	t_vector	right;
	t_vector	forward;
	t_vector	origin;
}					t_matrix;

void				trace_ray(t_scene *scene);
int					intersect(t_scene *scene);
void				install_cams(t_scene *scene);
t_closest			sp_intersect(void *data, t_vector eye, t_vector dir,
						t_limit lim);
t_closest			pl_intersect(void *data, t_vector eye, t_vector dir,
						t_limit lim);
t_closest			tr_intersect(void *data, t_vector eye, t_vector dir,
						t_limit lim);
t_closest			sq_intersect(void *data, t_vector eye, t_vector dir,
						t_limit lim);
t_closest			cy_intersect(void *data, t_vector eye, t_vector dir,
						t_limit lim);
float				lightning(t_scene *scene);
float				make_specular(t_vector n, t_vector l, t_vector ray,
						float ratio);
float				light_point(t_vector n, t_vector l, float ratio);
float				compute_lightning(t_scene *scene, t_light *light,
						t_vector intersect, t_vector n);
t_color				compute_color(t_closest closest, t_scene *scene);
void				draw_image(t_scene *scene, int is_save);

#endif

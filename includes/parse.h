/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:33:34 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 16:34:23 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_res
{
	int				check;
	int				width;
	int				height;
	float			ratio;
}					t_res;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_amb
{
	int				check;
	float			ratio;
	t_color			rgb;
}					t_amb;

typedef struct s_cam
{
	t_vector		vec;
	t_vector		n_vec;
	float			fov;
	double			v_width;
	double			v_height;
	double			x_pixel;
	double			y_pixel;
	struct s_cam	*next;
}					t_cam;

typedef struct s_light
{
	int				check;
	t_vector		vec;
	float			ratio;
	t_color			rgb;
	struct s_light	*next;
}					t_light;

typedef struct s_sp
{
	t_vector		vec;
	float			d;
	t_color			rgb;
}					t_sp;

typedef struct s_pl
{
	t_vector		vec;
	t_vector		n_vec;
	t_color			rgb;
}					t_pl;

typedef struct s_cy
{
	t_vector		vec;
	t_vector		n_vec;
	float			d;
	float			h;
	t_color			rgb;
}					t_cy;

typedef struct s_sq
{
	t_vector		vec;
	t_vector		n_vec;
	float			side;
	t_color			rgb;
}					t_sq;

typedef struct s_tr
{
	t_vector		v1;
	t_vector		v2;
	t_vector		v3;
	t_color			rgb;
	t_vector		norm;
	t_pl			pl;
	double			d;
}					t_tr;

typedef struct s_closest
{
	double			length;
	float			color;
	t_vector		intersect;
	t_vector		norm;
	t_color			rgb;
}					t_closest;

typedef struct s_limit
{
	float		min;
	float		max;
}					t_limit;

enum e_type
{
	SPHERE,
	TRIANGLE,
	PLANE,
	SQUARE,
	CYLINDER
};

typedef struct s_object
{
	enum e_type		type;
	t_closest		(*equation)(void *data, t_vector start,
					t_vector ray, t_limit lim);
	void			*data;
	void			*next;
}					t_object;

typedef struct s_scene
{
	void			*mlx;
	void			*window;
	t_limit			lim;
	t_vector		ray;
	t_data			img;
	t_res			res;
	t_amb			amb;
	t_cam			*first_cam;
	t_cam			*cams;
	t_light			*light;
	t_object		*objs;
}					t_scene;

void				ft_check_line(char *line, t_scene *scene);
void				read_and_parse_file(char *filename, t_scene **scene);
void				parser(char *line, t_scene *scene);
void				parse_resolution(char *line, t_scene *scene);
void				parse_ambient(char *line, t_scene *scene);
void				parse_camera(char *line, t_scene *scene);
void				parse_light(char *line, t_scene *scene);
void				parse_sphere(char *line, t_scene *scene);
void				parse_plane(char *line, t_scene *scene);
void				parse_cylinder(char *line, t_scene *scene);
void				parse_square(char *line, t_scene *scene);
void				parse_triangle(char *line, t_scene *scene);

#endif

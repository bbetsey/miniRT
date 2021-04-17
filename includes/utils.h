#ifndef UTILS_H
# define UTILS_H

void		error_handler(char *str, t_scene *scene);
int			rt_strcmp(char	*s1, char *s2);
char		**rt_split(char const *s, char *c);
int			rt_atoi(const char *str);
float		rt_atof(char *str);
void		*ft_bzero(void *s, size_t n);
void		print_scene(t_scene *scene);
void		check_scene(t_scene *scene);
void		check_rgb(t_color rgb, t_scene *scene);
void		check_normal(t_vector n, t_scene *scene);
void		free_array(char **arr);
void		free_scene(t_scene *scene);
int			arr_len(char **arr);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
t_vector	rotate_normal(t_vector dir, t_vector norm);
t_color		color_sum(t_color c1, t_color c2);
t_color		color_mix(t_color c1, t_color c2);
t_color		color_multi(t_color c, double i);
t_color		color_div(t_color c, double i);
t_vector	make_ray(double x, double y, t_cam *cam);
void		next_camera(t_scene *scene);
void		operator(t_scene *scene, int key_code);
int			ft_key(int key_code, t_scene *scene);
void		print_square(t_object *square);
void		print_triangle(t_object *triangle);
void		print_cylinder(t_object *cylinder);
void		print_sphere(t_object *sphere);
void		print_plane(t_object *plane);
int			red_button(t_scene *scene);
void		exit_minirt(t_scene *scene);
void		save_image(t_scene *scene, char *filename);
void		install_window(t_scene *scene);
void		create_image(t_scene *scene);
void		print_command(int key_code);
void		change_dir_operator(t_scene *scene, int key_code);
int			check_dir(int key_code);
void		check_resolution(t_scene *scene);
void		install_start_end_x_y(t_scene *scene);
t_vector	vec_rotate_y(t_vector vec, int angle);
t_vector	vec_rotate_x(t_vector vec, int angle);

#endif

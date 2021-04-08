/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:52:29 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/08 21:49:07 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_check_line(char *line, t_scene *scene)
{
	while (*line)
	{
		if ((*line < 48 || *line > 57) && *line != ' ' && *line
		!= '\t' && *line != '.' && *line != ',' && *line != '-')
			error_handler("Extra characters", scene);
		line++;
	}
}

void		parser(char *line, t_scene *scene)
{
	if (!line)
		error_handler("no line", scene);
	if (line[0] == 'R')
		parse_resolution(&line[1], scene);
	else if (line[0] == 'A')
		parse_ambient(&line[1], scene);
	else if (line[0] == 'c' && line[1] == 'y')
		parse_cylinder(&line[2], scene);
	else if (line[0] == 's' && line[1] == 'p')
		parse_sphere(&line[2], scene);
	else if (line[0] == 'p' && line[1] == 'l')
		parse_plane(&line[2], scene);
	else if (line[0] == 's' && line[1] == 'q')
		parse_square(&line[2], scene);
	else if (line[0] == 't' && line[1] == 'r')
		parse_triangle(&line[2], scene);
	else if (line[0] == 'c')
		parse_camera(&line[1], scene);
	else if (line[0] == 'l')
		parse_light(&line[1], scene);
}

int			ft_check_file(char *filename, t_scene *scene)
{
	int		i;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) <= 0)
		error_handler("Can't open map", scene);
	i = 0;
	while (filename[i] != '.' && filename[i])
		i++;
	if (!filename[i])
		error_handler("Incorrect file extension", scene);
	if (rt_strcmp(&filename[i], ".rt"))
		error_handler("Incorrect file extension", scene);
	return (fd);
}

t_scene		*scene_init(t_scene *scene)
{
	if (!(scene = malloc(sizeof(t_scene))))
		error_handler("Can't allocate memory for scene", scene);
	scene->res.check = 0;
	scene->amb.check = 0;
	scene->mlx = 0;
	scene->window = 0;
	scene->light = 0;
	scene->cams = 0;
	scene->objs = 0;
	return (scene);
}

void		read_and_parse_file(char *filename, t_scene **scene)
{
	int		fd;
	int		ret;
	char	*line;

	fd = ft_check_file(filename, *scene);
	(*scene) = scene_init(*scene);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		parser(line, *scene);
		free(line);
	}
	parser(line, *scene);
	check_scene(*scene);
	free(line);
}

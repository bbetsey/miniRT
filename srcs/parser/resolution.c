#include "minirt.h"

void	parse_resolution(char *line, t_scene *scene)
{
	char	**arr;

	ft_check_line(line, scene);
	arr = rt_split(line, " \t");
	if (arr_len(arr) != 2)
		error_handler("invalid number of arguments for resolution", scene);
	scene->res.width = rt_atoi(arr[0]);
	scene->res.height = rt_atoi(arr[1]);
	if (scene->res.width < 0)
		error_handler("resolution width must be positive", scene);
	if (scene->res.width == 0)
		error_handler("resolution width must be more then zero", scene);
	if (scene->res.height < 0)
		error_handler("resolution height must be positive", scene);
	if (scene->res.height == 0)
		error_handler("resolution height must be more then zero", scene);
	scene->res.check = 1;
	check_resolution(scene);
	free_array(arr);
}

#include "minirt.h"

void	check_resolution(t_scene *scene)
{
	int		sizex;
	int		sizey;

	mlx_get_screen_size(&sizex, &sizey);
	if (scene->res.width > sizex)
	{
		scene->res.width = sizex;
		printf(BOLDYELLOW "Too large reolution width." RESET
			" New width: %d\n", scene->res.width);
	}
	if (scene->res.height > sizey)
	{
		scene->res.height = sizey;
		printf(BOLDYELLOW "Too large reolution height." RESET
			" New height: %d\n", scene->res.height);
	}
}

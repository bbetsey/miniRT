#include "minirt.h"

t_color	color_mix(t_color c1, t_color c2)
{
	t_color	mix;

	mix.r = c1.r * c2.r / 255;
	mix.g = c1.g * c2.g / 255;
	mix.b = c1.b * c2.b / 255;
	return (mix);
}

t_color	color_sum(t_color c1, t_color c2)
{
	t_color	mix;

	mix.r = c1.r + c2.r;
	mix.g = c1.g + c2.g;
	mix.b = c1.b + c2.b;
	return (mix);
}

t_color	color_multi(t_color c, double i)
{
	c.r *= i;
	c.g *= i;
	c.b *= i;
	return (c);
}

t_color	color_div(t_color c, double i)
{
	c.r /= i;
	c.g /= i;
	c.b /= i;
	return (c);
}

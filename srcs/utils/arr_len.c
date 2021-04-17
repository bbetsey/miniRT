#include "minirt.h"

int	arr_len(char **arr)
{
	int		len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

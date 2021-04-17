#include "minirt.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	rt_atoi(const char *str)
{
	int		sign;
	long	result;
	long	next;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		next = result * 10 + (*str - 48);
		if (next < result)
			return (0);
		result = next;
		str++;
	}
	result = (int)result;
	return (result * sign);
}

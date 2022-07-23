#include "minirt.h"

int	main(int argc, char *argv[])
{
	// t_scene *scene;

	(void)argc;
	(void)argv;
	// if (argc != 2)
	// 	ft_error("USAGE : \"./miniRT [MAP.rt]\n\"", 1);
	// printf("%f\n", pow(0.1, 2));
	printf("printf %f\n", ft_atod("0.01"));
	printf("printf %f\n", ft_atod("012.34"));
	printf("printf %f\n", ft_atod("-12.34"));
	printf("printf %f\n", ft_atod("0"));
	return (0);
}

void	ft_error(const char *errmsg, int errcode)
{
	write(2, "Error\n", 6);
	write(2, errmsg, ft_strlen(errmsg));
	exit(errcode);
}

// double	atod(char *str)
// { //double d[0]:sign | d[1]: number(정수부) | d[2]: point(소수부)
//  	int		idx;
// 	double	d[3];

// 	idx = 0;
// 	ft_bzero(d, 3);
// 	if (str[idx] == '-' || str[idx] == '+')
// 	{
// 		d[0] = 1;
// 		if (str[idx] == '-')
// 			d[0] = -1;
// 		idx += 1;
// 	}
// 	while (str[idx])
// 	{
// 		if (str[idx] == '.')
// 		{
// 			idx += 1;
// 			break;
// 		}
// 		d[1] = (d[1] * 10) + (str[idx] - '0');
// 		idx += 1;
// 	}
// 	while (str[idx])
// 	{
// 		d[2] = (d[2] / 10) + (str[idx] - '0') * 0.1;
// 		idx += 1;
// 	}
// 	return (d[0] * (d[1] + d[2]));
// }

double	ft_atod(char *str)
{
	double		result;
	const char	*point = ft_strchr(str, '.');
	const int	sign = -(*str == '-') * 2 + 1;
	int			idx;

	if (!point)
		return (ft_atoi(str));
	if (*str == '-' || *str == '+')
		str += 1;
	result = 0.0;
	idx = 0;
	while (point - idx > str)
	{
		idx += 1;
		result = result + ((*(point - idx) - '0') * pow(10, idx - 1));
	}
	idx = 1;
	while (point[idx])
	{
		result = result + ((point[idx] - '0') * pow(0.1, idx));
		idx += 1;
	}
	return (sign * result);
}

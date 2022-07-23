#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_scene *scene;

	// (void)argc;
	// (void)argv;
	if (argc != 2)
		ft_error("USAGE : \"./so_long [MAP.rt]\"\n", 1);
	scene = init_scene(argv[1]);
	// (void)scene;
	return (0);
}

void	ft_error(const char *errmsg, int errcode)
{
	write(2, "Error\n", 6);
	write(2, errmsg, ft_strlen(errmsg));
	exit(errcode);
}

double	ft_atod(char *str)
{
	double		result;
	int			idx;
	const char	*point = ft_strchr(str, '.');
	const int	sign = -(*str == '-') * 2 + 1;

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

t_vec	vec3(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point	point3(double x, double y, double z)
{
	t_vec	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_color	color3(double r, double g, double b)
{
	t_color	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

double	vlen(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

double	vinner(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec	vouter(t_vec vec1, t_vec vec2)
{
	t_vec	outer;

	outer.x = vec1.y * vec2.z - vec1.z * vec2.y;
	outer.y = vec1.z * vec2.x - vec1.x * vec2.z;
	outer.z = vec1.x * vec2.y - vec1.y * vec2.x;
}

t_vec	vunit(t_vec vec)
{
	const double	len = vlen(vec);

	if (len == 0)
		ft_error("Divide by 0\n", 1);
	return (vdivide(vec, vec3(len, len, len)));
}

t_vec	vplus(t_vec vec1, t_vec vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}

t_vec	vminus(t_vec vec1, t_vec vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_vec	vmult(t_vec vec1, t_vec vec2)
{
	vec1.x *= vec2.x;
	vec1.y *= vec2.y;
	vec1.z *= vec2.z;
	return (vec1);
}

t_vec	vdivide(t_vec vec1, t_vec vec2)
{
	vec1.x /= vec2.x;
	vec1.y /= vec2.y;
	vec1.z /= vec2.z;
	return (vec1);
}

t_vec	vmin(t_vec vec1, t_vec vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

t_scene	*init_scene(const char *file)
{
	t_scene		*scene;
	const int	fd = open(file, O_RDONLY);
	char		*line;

	if (fd == -1)
		ft_error("No such file or directory\n", 2);
	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	return (scene);
}

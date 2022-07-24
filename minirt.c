#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_scene *scene;

	// (void)argc;
	// (void)argv;
	if (argc != 2)
		ft_error("USAGE : \"./miniRT [MAP.rt]\"\n", 1);
	scene = init_scene(argv[1]);
	(void)scene;
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
	return (outer);
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
	if (!scene)
		ft_error("MALLOC FAILED\n", 1);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		read_element(line, scene);
		free(line);
	}
	return (scene);
}

void	read_element(char *line, t_scene *scene)
{
	char	**element;

	element = ft_split(line, ' ');
	if (!element[0])
		;
	else if (!ft_strncmp(element[0], "A", -1))
		read_ambient(element, scene);
	else if (!ft_strncmp(element[0], "C", -1))
		read_camera(element, scene);
	else if (!ft_strncmp(element[0], "L", -1))
		;
	else if (!ft_strncmp(element[0], "sp", -1))
		;
	else if (!ft_strncmp(element[0], "pl", -1))
		;
	else if (!ft_strncmp(element[0], "cy", -1))
		;
	free_split(element);
}

void	read_ambient(char **element, t_scene *scene)
{
	if (!element[1] || !element[2] || element[3])
		ft_error("A [RATIO] [R,G,B]\n", 1);
	if (!ft_isdouble(element[1]))
		ft_error("WRONG Ambient ratio\n", 1);
	scene->ambient.ratio = ft_atod(element[1]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		ft_error("WRONG Ambient ratio\n", 1);
	scene->ambient.color = read_rgb(element[2], "WRONG Ambient color\n");
}

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i += 1;
	}
	free(splited);
}

int	ft_isdouble(char *str)
{
	int	point;

	point = 0;
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.')
			return (FALSE);
		if (*str == '.')
			point += 1;
		if (*str == '.' && point > 1)
			return (FALSE);
		str += 1;
	}
	return (TRUE);
}

int	ft_isint(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (FALSE);
	}
	return (TRUE);
}

int	ft_isrgb(double color)
{
	return (color >= 0.0 && color < 256.0);
}

int	ft_isunit(double xyz)
{
	return (xyz >= -1.0 && xyz <= 1.0);
}

t_color	read_rgb(char *rgb, const char *errmsg)
{
	t_color	color;
	char	**rgbs;
	int		i;

	rgbs = ft_split(rgb, ',');
	i = 0;
	while (rgbs[i])
	{
		if (!ft_isint(rgbs[i]))
			ft_error(errmsg, 1);
		i += 1;
	}
	if (i != 3)
		ft_error(errmsg, 1);
	color = color3(ft_atod(rgbs[0]), ft_atod(rgbs[1]), ft_atod(rgbs[2]));
	if (!ft_isrgb(color.x) || !ft_isrgb(color.y) || !ft_isrgb(color.z))
		ft_error(errmsg, 1);
	free_split(rgbs);
	return (color);
}

t_vec	read_vec(char *vec, const char *errmsg)
{
	t_vec	vunit;
	char	**xyz;
	int		i;

	xyz = ft_split(vec, ',');
	i = 0;
	while (xyz[i])
	{
		if (!ft_isdouble(xyz[i]))
			ft_error(errmsg, 1);
		i += 1;
	}
	if (i != 3)
		ft_error(errmsg, 1);
	vunit = vec3(ft_atod(xyz[0]), ft_atod(xyz[1]), ft_atod(xyz[2]));
	if (!ft_isunit(vunit.x) || !ft_isunit(vunit.y) || !ft_isunit(vunit.z))
		ft_error(errmsg, 1);
	free_split(xyz);
	return (vunit);
}

t_point	read_coor(char *coor, const char *errmsg)
{
	t_point	point;
	char	**xyz;
	int		i;

	xyz = ft_split(coor, ',');
	i = 0;
	while (xyz[i])
	{
		if (!ft_isdouble(xyz[i]))
			ft_error(errmsg, 1);
		i += 1;
	}
	if (i != 3)
		ft_error(errmsg, 1);
	point = point3(ft_atod(xyz[0]), ft_atod(xyz[1]), ft_atod(xyz[2]));
	free_split(xyz);
	return (point);
}

void	read_camera(char **element, t_scene *scene)
{
	if (!element[1] || !element[2] || !element[3] || element[4])
		ft_error("C [COOR] [ORIENTATION] [FOV]\n", 1);
	scene->camera.coor = read_coor(element[1], "WRONG Camera coordinate\n");
	scene->camera.orientation = read_vec(element[2], "WRONG Camera vector\n");
	if (!ft_isint(element[3]))
		ft_error("WRONG Camera FOV\n", 1);
	scene->camera.fov = ft_atoi(element[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		ft_error("WRONG Camera FOV\n", 1);
}

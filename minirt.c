#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_scene *scene;

	if (argc != 2 || !ft_strrchr(argv[1], '.') || ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", -1))
		ft_error("USAGE : \"./miniRT [MAP.rt]\"\n", 1);
	scene = init_scene(argv[1]);
	// print_scene(scene); // check file reading
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
	mlx_set_exit(scene);
	mlx_loop(scene->mlx);
	return (0);
}

void	ft_error(const char *errmsg, int errcode)
{
	write(2, "Error\n", 6);
	write(2, errmsg, ft_strlen(errmsg));
	exit(errcode);
}

int	exit_minirt(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	exit(0);
	return (0);
}

int	key_press(int key_code, t_scene *scene)
{
	if (key_code == KEY_ESC)
		exit_minirt(scene);
	return (0);
}

void	mlx_set_exit(t_scene *scene)
{
	mlx_key_hook(scene->win, &key_press, scene);
	mlx_hook(scene->win, KEY_EXIT, 0, &exit_minirt, scene);
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
	check_environment(scene->environment);
	init_mlx(scene);
	return (scene);
}

void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "miniRT");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img.addr = mlx_get_data_addr(
		scene->img.img,
		&scene->img.bits_per_pixel,
		&scene->img.size_line,
		&scene->img.endian);
}

void	check_environment(int flag)
{
	if ((flag & AMBIENT) == 0)
		ft_error("THERE IS NO AMBIENT\n", 1);
	if ((flag & CAMERA) == 0)
		ft_error("THERE IS NO CAMERA\n", 1);
	if ((flag & LIGHT) == 0)
		ft_error("THERE IS NO LIGHT\n", 1);
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
		read_light(element, scene);
	else if (!ft_strncmp(element[0], "sp", -1))
		read_sphere(element, scene);
	else if (!ft_strncmp(element[0], "pl", -1))
		read_plane(element, scene);
	else if (!ft_strncmp(element[0], "cy", -1))
		read_cylinder(element, scene);
	else
		ft_error("WRONG Argument identifier\n", 1);
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
	scene->environment |= AMBIENT;
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
	if (!vunit.x && !vunit.y && !vunit.z)
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
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
		ft_error("WRONG Camera FOV\n", 1);
	scene->environment |= CAMERA;
}

void	read_light(char **element, t_scene *scene)
{
	if (!element[1] || !element[2] || element[3])
		ft_error("L [COOR] [BRIGHTNESS RATIO]\n", 1);
	scene->light.coor = read_coor(element[1], "WRONG Light coordinate\n");
	if (!ft_isdouble(element[2]))
		ft_error("WRONG Light ratio\n", 1);
	scene->light.ratio = ft_atod(element[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		ft_error("WRONG Light ratio\n", 1);
	scene->environment |= LIGHT;
}

t_obj	*object(int type, void *element)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj)
		ft_error("MALLOC FAILED\n", 1);
	obj->type = type;
	obj->element = element;
	obj->next = NULL;
	return (obj);
}

void	obj_add_back(t_scene *scene, t_obj *new)
{
	t_obj	*cur;

	if (!scene->objs)
		scene->objs = new;
	else
	{
		cur = scene->objs;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	read_sphere(char **element, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error("MALLOC FAILED\n", 1);
	if (!element[1] || !element[2] || !element[3] || element[4])
		ft_error("sp [COOR] [DIAMETER] [R,G,B]\n", 1);
	sphere->coor = read_coor(element[1], "WRONG Sphere coordinate\n");
	if (!ft_isdouble(element[2]))
		ft_error("WRONG Sphere diameter\n", 1);
	sphere->radius = ft_atod(element[2]) / 2.0;
	sphere->color = read_rgb(element[3], "WRONG Sphere color\n");
	if (sphere->radius < 0.0)
		ft_error("WRONG Sphere diameter\n", 1);
	obj_add_back(scene, object(SPHERE, sphere));
}

void	read_plane(char **element, t_scene *scene)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		ft_error("MALLOC FAILED\n", 1);
	if (!element[1] || !element[2] || !element[3] || element[4])
		ft_error("pl [COOR] [ORIENTATION] [R,G,B]\n", 1);
	plane->coor = read_coor(element[1], "WRONG Plane coordinate\n");
	plane->orientation = read_vec(element[2], "WRONG Plane vector\n");
	plane->color = read_rgb(element[3], "WRONG Plane color\n");
	obj_add_back(scene, object(PLANE, plane));
}

void	read_cylinder(char **elem, t_scene *scene)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		ft_error("MALLOC FAILED\n", 1);
	if (!elem[1] || !elem[2] || !elem[3] || !elem[4] || !elem[5] || elem[6])
		ft_error("cy [COOR] [ORIENTATION] [DIAMETER] [HEIGHT] [R,G,B]\n", 1);
	cy->coor = read_coor(elem[1], "WRONG Cylinder coordinate\n");
	cy->orientation = read_vec(elem[2], "WRONG Cylinder vector\n");
	if (!ft_isdouble(elem[3]))
		ft_error("WRONG Cylinder diameter\n", 1);
	cy->radius = ft_atod(elem[3]) / 2.0;
	if (!ft_isdouble(elem[4]))
		ft_error("WRONG Cylinder height\n", 1);
	cy->height = ft_atod(elem[4]);
	cy->color = read_rgb(elem[5], "WRONG Cylinder color\n");
	if (cy->radius < 0.0)
		ft_error("WRONG Cylinder diameter\n", 1);
	if (cy->height < 0.0)
		ft_error("WRONG Cylinder height\n", 1);
	obj_add_back(scene, object(CYLINDER, cy));
}

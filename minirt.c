#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_scene *scene;

	if (argc != 2 || !ft_strrchr(argv[1], '.') || ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", -1))
		ft_error("USAGE : \"./miniRT [MAP.rt]\"\n", 1);
	scene = init_scene(argv[1]);
	// print_scene(scene); // check file reading
	draw_scene(scene);
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
	mlx_destroy_image(scene->mlx, scene->img.img);
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
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
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

t_ray	ray(t_point	origin, t_vec	direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vunit(direction);
	return (ray);
}

t_point	ray_at(t_ray *ray, double t)
{
	t_point	at;
	t_vec	len;

	len = vmult(ray->direction, vec3(t, t, t));
	at = vplus(ray->origin, len);
	return (at);
}

t_scene	*init_scene(const char *file)
{
	t_scene		*scene;

	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (!scene)
		ft_error("MALLOC FAILED\n", 1);
	get_element(file, scene);
	init_viewport(scene);
	init_mlx(scene);
	return (scene);
}

void	init_viewport(t_scene *scene)
{
	const t_vec	cam = scene->camera.orientation;
	t_vec		up;
	t_point		temp;

	if (fabs(cam.x) < EPSILON && fabs(cam.z) < EPSILON)
		up = vec3(0, 0, 1);
	else
		up = vec3(0, 1, 0);
	scene->viewport.origin = scene->camera.coor;
	print_vec("camera.origin\t", scene->viewport.origin);
	scene->viewport.horizontal = vunit(vouter(cam, up));
	print_vec("viewport.horizontal\t", scene->viewport.horizontal);
	scene->viewport.vertical = vunit(vouter(scene->viewport.horizontal, cam));
	print_vec("viewport.vertical\t", scene->viewport.vertical);
	scene->viewport.focal_len = WIDTH / 2 / get_tan(scene->camera.fov / 2);
	temp = vplus(scene->viewport.origin, vmult(cam, vec3(scene->viewport.focal_len, scene->viewport.focal_len, scene->viewport.focal_len)));
	print_vec("viewport.center\t", temp);
	temp = vminus(temp, vmult(scene->viewport.horizontal, vec3(WIDTH / 2, WIDTH / 2, WIDTH / 2)));
	print_vec("viewport.left_side\t", temp);
	temp = vminus(temp, vmult(scene->viewport.vertical, vec3(HEIGHT / 2, HEIGHT / 2, HEIGHT / 2)));
	print_vec("viewport.left_bottom\t", temp);
	scene->viewport.left_bottom = temp;
}

double	get_tan(double	degree)
{
	return (tan(degree * (M_PI / 180)));
}

void	get_element(const char *file, t_scene *scene)
{
	const int	fd = open(file, O_RDONLY);
	char		*line;
	int			idx_newline;

	if (fd == -1)
		ft_error("No such file or directory\n", 2);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		idx_newline = ft_strlen(line) - 1;
		if (line[idx_newline] == '\n')
			line[idx_newline] = '\0';
		read_element(line, scene);
		free(line);
	}
	close(fd);
	check_environment(scene->environment);
}

void	init_mlx(t_scene *scene)
{
	// leaks_miniRT(1);
	scene->mlx = mlx_init();
	// leaks_miniRT(2);
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
	scene->camera.orientation = vunit(read_vec(element[2], "WRONG Camera vector\n"));
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
	plane->orientation = vunit(read_vec(element[2], "WRONG Plane vector\n"));
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
	cy->orientation = vunit(read_vec(elem[2], "WRONG Cylinder vector\n"));
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

void	draw_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	int		rgb;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_primary(scene->viewport, x, y);
			// print_vec("ray :", ray.direction);
			rgb = get_rgb(ray_color(ray, scene));
			put_pixel_on_img(&scene->img, x, HEIGHT - 1 - y, rgb);
			x += 1;
		}
		y += 1;
	}
}

t_ray	ray_primary(t_viewport viewport, int x, int y)
{
	t_ray	ray;
	t_point	point;
	t_vec	temp;

	ray.origin = viewport.origin;
	point = viewport.left_bottom;
	temp = vmult(viewport.horizontal, vec3(x, x, x));
	point = vplus(point, temp);
	temp = vmult(viewport.vertical, vec3(y, y, y));
	point = vplus(point, temp);
	ray.direction = vminus(point, ray.origin);
	return (ray);
}

t_color ray_color(t_ray ray, t_scene *scene)
{
	t_hit_record	rec;

	rec.tmin = EPSILON;
	rec.tmax = INFINITY;
	if (hit(scene->objs, &ray, &rec))
		return (phong_lightning(scene, rec));
	return (color3(0.0, 0.0, 0.0));
}

void	put_pixel_on_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_rgb(t_color color)
{
	int	rgb;

	rgb = 0;
	rgb |= (int)color.x << 16;
	rgb |= (int)color.y << 8;
	rgb |= (int)color.z;
	return (rgb);
}

int	hit(t_obj *objs, t_ray *ray, t_hit_record *rec)
{
	t_obj	*obj;
	int		hit_anything;

	obj = objs;
	hit_anything = 0;
	while (obj)
	{
		if (obj->type == PLANE)
			hit_anything |= hit_plane(obj->element, ray, rec);
		if (obj->type == SPHERE)
			hit_anything |= hit_sphere(obj->element, ray, rec);
		if (obj->type == CYLINDER)
			hit_anything |= hit_cylinder(obj->element, ray, rec);
		obj = obj->next;
	}
	return (hit_anything);
}

int	hit_plane(t_plane *pl, t_ray *ray, t_hit_record *rec)
{
	const double	denominator = vinner(pl->orientation, ray->direction);
	double			root;

	if (fabs(denominator) < EPSILON)
		return (FALSE);
	root = vinner(vminus(pl->coor, ray->origin), pl->orientation) / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);
	rec->t = root;
	rec->tmax = rec->t;
	rec->p = ray_at(ray, root);
	rec->normal = pl->orientation;
	rec->front_face = vinner(ray->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vmult(rec->normal, vec3(-1, -1, -1));
	rec->albedo = pl->color;
	return (TRUE);
}

int	hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
	const t_vec		oc = vminus(ray->origin, sp->coor);
	const double	a = vlen(ray->direction) * vlen(ray->direction);
	const double	b = vinner(oc, ray->direction);
	const double	c = vlen(oc) * vlen(oc) - sp->radius * sp->radius;
	double			root;

	if (b * b - a * c < 0)
		return (FALSE);
	root = (-b - sqrt(b * b - a * c)) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrt(b * b - a * c)) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->tmax = rec->t;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->coor), vec3(sp->radius, sp->radius, sp->radius));
	rec->front_face = vinner(ray->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vmult(rec->normal, vec3(-1, -1, -1));
	rec->albedo = sp->color;
	return (TRUE);
}

int	hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double	discriminant;
	double	a;
	double	b;
	double	c;
	double	root;

	t_vec	ch;
	t_vec	w;

	ch = cy->orientation;
	w = vminus(ray->origin, cy->coor);
	a = vinner(ray->direction, ray->direction) - pow(vinner(ray->direction, ch), 2);
	b = vinner(ray->direction, w) - (vinner(ray->direction, ch) * vinner(w, ch));
	c = vinner(w, w) - vinner(w, ch) * vinner(w, ch) - (cy->radius * cy->radius);
	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (FALSE);
	root = (-b - sqrt(discriminant)) / a;
	if (root < rec->tmin || root > rec->tmax || vinner(vminus(ray_at(ray, root), cy->coor), ch) < 0 || vinner(vminus(ray_at(ray, root), cy->coor), ch) > cy->height)
	{
		// return (FALSE);
		root = (-b + sqrt(discriminant)) / a;
		if (root < rec->tmin || root > rec->tmax || vinner(vminus(ray_at(ray, root), cy->coor), ch) < 0 || vinner(vminus(ray_at(ray, root), cy->coor), ch) > cy->height)
			return (FALSE);
	}
	rec->t = root;
	rec->tmax = rec->t;
	rec->p = ray_at(ray, root);
	rec->normal = vouter(cy->orientation, vouter(vminus(rec->p, cy->coor), cy->orientation));
	rec->front_face = vinner(ray->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vmult(rec->normal, vec3(-1, -1, -1));
	rec->albedo = cy->color;
	return (TRUE);
}

t_color	phong_lightning(t_scene *scene, t_hit_record rec)
{
	t_vec		light_dir = vminus(scene->light.coor, rec.p);
	double		light_len = vlen(light_dir);
	const t_ray	light_ray = ray(vplus(rec.p, vmult(rec.normal, vec3(EPSILON, EPSILON, EPSILON))), light_dir);
	t_color		ambient = vmult(scene->ambient.color, vec3(scene->ambient.ratio, scene->ambient.ratio, scene->ambient.ratio));
	t_color		diffuse;
	double		kd;

	light_dir = vunit(light_dir);
	ambient = vmult(ambient, vec3(rec.albedo.x / 255, rec.albedo.y / 255, rec.albedo.z / 255));
	kd = fmax(vinner(rec.normal, light_dir), 0.0);
	diffuse = vmult(rec.albedo, vec3(kd, kd, kd));
	diffuse = vmult(diffuse, vec3(scene->light.ratio, scene->light.ratio, scene->light.ratio));
	if (in_shadow(scene->objs, light_ray, light_len))
		diffuse = color3(0, 0, 0);
	return (vmin(vplus(diffuse, ambient), color3(255, 255, 255)));
}

int	in_shadow(t_obj	*objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = EPSILON;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

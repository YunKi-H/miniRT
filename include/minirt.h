#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
// write read
# include <stdlib.h>
// malloc free exit
# include <stdio.h>
// printf perror
# include <string.h>
// strerror
# include <fcntl.h>
// open close
# include <math.h>
// sqrt pow fmax ..
# include "../../libft/libft.h"
# include "get_next_line.h"
# include "../minilibx_mms/mlx.h"
# define WIDTH 1080
# define HEIGHT 720
# define KEY_ESC 53
# define KEY_EXIT 17
# define EPSILON 1e-6

typedef struct s_vec		t_vec;
typedef struct s_vec		t_point;
typedef struct s_vec		t_color;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_ray		t_ray;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_scene		t_scene;
typedef struct s_obj		t_obj;
typedef struct s_image		t_image;
typedef struct s_viewport	t_viewport;
typedef struct s_hit_record	t_hit_record;

enum e_bool
{
	FALSE,
	TRUE
};

enum e_type
{
	AMBIENT = 1 << 0,
	CAMERA = 1 << 1,
	LIGHT = 1 << 2,
	PLANE = 1 << 3,
	SPHERE = 1 << 4,
	CYLINDER = 1 << 5
};

// struct
struct s_vec
{
	double	x;
	double	y;
	double	z;
};

struct s_ambient
{
	double	ratio;
	t_color	color;
};

struct s_camera
{
	t_point	coor;
	t_vec	orientation;
	int		fov;
};

struct s_light
{
	t_point	coor;
	double	ratio;
};

struct s_ray
{
	t_point	origin;
	t_vec	direction;
};

struct s_sphere
{
	t_point	coor;
	double	radius;
	t_color	color;
};

struct s_plane
{
	t_point	coor;
	t_vec	orientation;
	t_color	color;
};

struct s_cylinder
{
	t_point	coor;
	t_vec	orientation;
	double	radius;
	double	height;
	t_color	color;
};

struct s_obj
{
	int				type;
	void			*element;
	struct s_obj	*next;
};

struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
};

struct s_viewport
{
	t_point	origin;
	t_vec	horizontal;
	t_vec	vertical;
	double	focal_len;
	t_point	left_bottom;
};

struct s_hit_record
{
	t_point	p;
	t_vec	normal;
	double	tmin;
	double	tmax;
	double	t;
	int		front_face;
	t_color	albedo;
};

struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_obj			*objs;
	int				environment;
	t_viewport		viewport;
	void			*mlx;
	void			*win;
	t_image			img;
};

// vectors
t_vec	vec3(double x, double y, double z);
t_point	point3(double x, double y, double z);
t_color	color3(double r, double g, double b);
double	vlen(t_vec vec);
double	vinner(t_vec vec1, t_vec vec2);
t_vec	vouter(t_vec vec1, t_vec vec2);
t_vec	vunit(t_vec vec);
t_vec	vplus(t_vec vec1, t_vec vec2);
t_vec	vminus(t_vec vec1, t_vec vec2);
t_vec	vmult(t_vec vec1, t_vec vec2);
t_vec	vdivide(t_vec vec1, t_vec vec2);
t_vec	vmin(t_vec vec1, t_vec vec2);
// structs
t_ray	ray(t_point	origin, t_vec	direction);
t_point	ray_at(t_ray *ray, double t);
// parsing
t_scene	*init_scene(const char *file);
void	get_element(const char *file, t_scene *scene);
t_vec	read_vec(char *vec, const char *errmsg);
t_point	read_coor(char *coor, const char *errmsg);
t_color	read_rgb(char *rgb, const char *errmsg);
void	read_element(char *line, t_scene *scene);
void	read_ambient(char **element, t_scene *scene);
void	read_camera(char **element, t_scene *scene);
void	read_light(char **element, t_scene *scene);
t_obj	*object(int type, void *element);
void	obj_add_back(t_scene *scene, t_obj *new);
void	read_sphere(char **element, t_scene *scene);
void	read_plane(char **element, t_scene *scene);
void	read_cylinder(char **elem, t_scene *scene);
void	check_environment(int flag);
void	init_viewport(t_scene *scene);
void	init_mlx(t_scene *scene);
// drawing
void	draw_scene(t_scene *scene);
t_ray	ray_primary(t_viewport viewport, int x, int y);
t_color ray_color(t_ray ray, t_scene *scene);
void	put_pixel_on_img(t_image *img, int x, int y, int color);
int		get_rgb(t_color color);
// tracing
int		hit(t_obj *objs, t_ray *ray, t_hit_record *rec);
int		hit_plane(t_plane *pl, t_ray *ray, t_hit_record *rec);
int		hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec);
int		hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec);
t_color	phong_lightning(t_scene *scene, t_hit_record rec);
// mlx
int		exit_minirt(t_scene *scene);
void	mlx_set_exit(t_scene *scene);
int		key_press(int key_code, t_scene *scene);
// utils
void	ft_error(const char *errmsg, int errcode);
double	ft_atod(char *str);
void	free_split(char **splited);
int		ft_isdouble(char *str);
int		ft_isint(char *str);
int		ft_isrgb(double color);
int		ft_isunit(double xyz);
double	get_tan(double	degree);

// debug
void	print_scene(t_scene *s);
void	leaks_miniRT(int idx);
void	print_vec(char *str, t_vec vec);

#endif

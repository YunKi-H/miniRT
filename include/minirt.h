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

typedef struct s_vec		t_vec;
typedef struct s_vec		t_point;
typedef struct s_vec		t_color;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_scene		t_scene;
typedef struct s_obj		t_obj;

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
	SPHERE = 1 << 3,
	PLANE = 1 << 4,
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

struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_obj		*objs;
	int			environment;
	void		*mlx;
	void		*win;
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
// parsing
t_scene	*init_scene(const char *file);
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
// utils
void	ft_error(const char *errmsg, int errcode);
double	ft_atod(char *str);
void	free_split(char **splited);
int		ft_isdouble(char *str);
int		ft_isint(char *str);
int		ft_isrgb(double color);
int		ft_isunit(double xyz);
void	check_environment(int flag);

// debug
void	print_scene(t_scene *s);

#endif

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
// write read
# include <stdlib.h>
// malloc free exit
# include <stdio.h>
// printf perror strerror
# include <fcntl.h>
// open close
# include <math.h>
// sqrt pow fmax ..
# include "../../libft/libft.h"
# include "get_next_line.h"

typedef struct s_vec		t_vec;
typedef struct s_vec		t_point;
typedef struct s_color		t_color;
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
	SPHERE,
	PLANE,
	CYLINDER
};

// struct
struct s_vec
{
	double	x;
	double	y;
	double	z;
};

struct s_color
{
	int	r;
	int	g;
	int	b;
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
	void		*mlx;
	void		*win;
};

// utils
void	ft_error(const char *errmsg, int errcode);
double	atod(char *str);
double	ft_atod(char *str);

#endif

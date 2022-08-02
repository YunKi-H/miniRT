/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:22:24 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:22:32 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

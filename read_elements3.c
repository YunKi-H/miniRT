/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:21:38 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:35:16 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	read_camera(char **element, t_scene *scene)
{
	if (!element[1] || !element[2] || !element[3] || element[4])
		ft_error("C [COOR] [ORIENTATION] [FOV]\n", 1);
	scene->camera.coor = read_coor(element[1], "WRONG Camera coordinate\n");
	scene->camera.orientation = vunit(read_vec(
				element[2],
				"WRONG Camera vector\n"));
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

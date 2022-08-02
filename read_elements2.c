/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:20:54 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:21:23 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

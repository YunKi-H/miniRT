/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_constructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:51 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:13:11 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

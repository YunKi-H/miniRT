/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:15:38 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:15:49 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

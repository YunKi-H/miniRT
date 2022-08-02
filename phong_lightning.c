/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lightning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:30:07 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:48:43 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	phong_lightning(t_scene *scene, t_hit_record rec)
{
	t_vec	light_dir;
	double	light_len;
	t_ray	light_ray;
	t_color	ambient;
	t_color	diffuse;

	light_dir = vminus(scene->light.coor, rec.p);
	light_len = vlen(light_dir);
	light_ray = ray(vplus(rec.p, vscale(rec.normal, EPSILON)), light_dir);
	light_dir = vunit(light_dir);
	ambient = vscale(scene->ambient.color, scene->ambient.ratio);
	ambient = vmult(ambient, \
	vec3(rec.albedo.x / 255, rec.albedo.y / 255, rec.albedo.z / 255));
	diffuse = vscale(rec.albedo, fmax(vinner(rec.normal, light_dir), 0.0));
	diffuse = vscale(diffuse, scene->light.ratio);
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

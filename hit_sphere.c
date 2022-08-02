/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:31:56 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:43:16 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	rec->normal = vdivide(vminus(rec->p, sp->coor), \
	vec3(sp->radius, sp->radius, sp->radius));
	rec->front_face = vinner(ray->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vscale(rec->normal, -1);
	rec->albedo = sp->color;
	return (TRUE);
}

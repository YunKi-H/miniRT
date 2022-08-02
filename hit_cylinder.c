/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:32:14 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 15:27:04 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	record_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec, double r)
{
	rec->t = r;
	rec->tmax = rec->t;
	rec->p = ray_at(ray, r);
	rec->normal = vouter(cy->orientation, \
	vouter(vminus(rec->p, cy->coor), cy->orientation));
	rec->front_face = vinner(ray->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vscale(rec->normal, -1);
	rec->albedo = cy->color;
}

int	hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double		abcdr[5];
	const t_vec	ch = cy->orientation;
	const t_vec	w = vminus(ray->origin, cy->coor);

	abcdr[0] = vinner(ray->direction, ray->direction) - \
	pow(vinner(ray->direction, ch), 2);
	abcdr[1] = vinner(ray->direction, w) - \
	(vinner(ray->direction, ch) * vinner(w, ch));
	abcdr[2] = vinner(w, w) - pow(vinner(w, ch), 2) - (cy->radius * cy->radius);
	abcdr[3] = abcdr[1] * abcdr[1] - abcdr[0] * abcdr[2];
	if (abcdr[3] < 0)
		return (FALSE);
	abcdr[4] = (-abcdr[1] - sqrt(abcdr[3])) / abcdr[0];
	abcdr[2] = vinner(vminus(ray_at(ray, abcdr[4]), cy->coor), ch);
	if (abcdr[4] < rec->tmin || abcdr[4] > rec->tmax || \
	abcdr[2] < 0 || abcdr[2] > cy->height)
	{
		abcdr[4] = (-abcdr[1] + sqrt(abcdr[3])) / abcdr[0];
		abcdr[2] = vinner(vminus(ray_at(ray, abcdr[4]), cy->coor), ch);
		if (abcdr[4] < rec->tmin || abcdr[4] > rec->tmax || \
		abcdr[2] < 0 || abcdr[2] > cy->height)
			return (FALSE);
	}
	record_cylinder(cy, ray, rec, abcdr[4]);
	return (TRUE);
}

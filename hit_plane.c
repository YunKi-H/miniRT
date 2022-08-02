/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:31:35 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:31:42 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_plane(t_plane *pl, t_ray *ray, t_hit_record *rec)
{
	const double	denominator = vinner(pl->orientation, ray->direction);
	double			root;

	if (fabs(denominator) < EPSILON)
		return (FALSE);
	root = vinner(vminus(pl->coor, ray->origin), pl->orientation) / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);
	rec->t = root;
	rec->tmax = rec->t;
	rec->p = ray_at(ray, root);
	rec->normal = pl->orientation;
	rec->front_face = vinner(ray->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vmult(rec->normal, vec3(-1, -1, -1));
	rec->albedo = pl->color;
	return (TRUE);
}

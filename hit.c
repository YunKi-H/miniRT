/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:31:10 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:31:22 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit(t_obj *objs, t_ray *ray, t_hit_record *rec)
{
	t_obj	*obj;
	int		hit_anything;

	obj = objs;
	hit_anything = 0;
	while (obj)
	{
		if (obj->type == PLANE)
			hit_anything |= hit_plane(obj->element, ray, rec);
		if (obj->type == SPHERE)
			hit_anything |= hit_sphere(obj->element, ray, rec);
		if (obj->type == CYLINDER)
			hit_anything |= hit_cylinder(obj->element, ray, rec);
		obj = obj->next;
	}
	return (hit_anything);
}

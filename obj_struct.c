/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:28:28 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:28:37 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*object(int type, void *element)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj)
		ft_error("MALLOC FAILED\n", 1);
	obj->type = type;
	obj->element = element;
	obj->next = NULL;
	return (obj);
}

void	obj_add_back(t_scene *scene, t_obj *new)
{
	t_obj	*cur;

	if (!scene->objs)
		scene->objs = new;
	else
	{
		cur = scene->objs;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operator1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:13:41 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:15:14 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vlen(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

double	vinner(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec	vouter(t_vec vec1, t_vec vec2)
{
	t_vec	outer;

	outer.x = vec1.y * vec2.z - vec1.z * vec2.y;
	outer.y = vec1.z * vec2.x - vec1.x * vec2.z;
	outer.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (outer);
}

t_vec	vunit(t_vec vec)
{
	const double	len = vlen(vec);

	if (len == 0)
		ft_error("Divide by 0\n", 1);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vec	vmin(t_vec vec1, t_vec vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operator2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:14:09 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:39:27 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vplus(t_vec vec1, t_vec vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}

t_vec	vminus(t_vec vec1, t_vec vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_vec	vmult(t_vec vec1, t_vec vec2)
{
	vec1.x *= vec2.x;
	vec1.y *= vec2.y;
	vec1.z *= vec2.z;
	return (vec1);
}

t_vec	vdivide(t_vec vec1, t_vec vec2)
{
	vec1.x /= vec2.x;
	vec1.y /= vec2.y;
	vec1.z /= vec2.z;
	return (vec1);
}

t_vec	vscale(t_vec vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

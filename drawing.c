/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:27:24 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:43:58 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	int		rgb;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_primary(scene->viewport, x, y);
			rgb = get_rgb(ray_color(ray, scene));
			put_pixel_on_img(&scene->img, x, HEIGHT - 1 - y, rgb);
			x += 1;
		}
		y += 1;
	}
}

t_ray	ray_primary(t_viewport viewport, int x, int y)
{
	t_ray	ray;
	t_point	point;
	t_vec	temp;

	ray.origin = viewport.origin;
	point = viewport.left_bottom;
	temp = vmult(viewport.horizontal, vec3(x, x, x));
	point = vplus(point, temp);
	temp = vmult(viewport.vertical, vec3(y, y, y));
	point = vplus(point, temp);
	ray.direction = vminus(point, ray.origin);
	return (ray);
}

t_color	ray_color(t_ray ray, t_scene *scene)
{
	t_hit_record	rec;

	rec.tmin = EPSILON;
	rec.tmax = INFINITY;
	if (hit(scene->objs, &ray, &rec))
		return (phong_lightning(scene, rec));
	return (color3(0.0, 0.0, 0.0));
}

void	put_pixel_on_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_rgb(t_color color)
{
	int	rgb;

	rgb = 0;
	rgb |= (int)color.x << 16;
	rgb |= (int)color.y << 8;
	rgb |= (int)color.z;
	return (rgb);
}

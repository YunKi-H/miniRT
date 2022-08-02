/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:17:04 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:41:15 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*init_scene(const char *file)
{
	t_scene	*scene;

	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (!scene)
		ft_error("MALLOC FAILED\n", 1);
	get_element(file, scene);
	init_viewport(scene);
	init_mlx(scene);
	return (scene);
}

void	init_viewport(t_scene *scene)
{
	const t_vec	cam = scene->camera.orientation;
	t_vec		up;
	t_point		tmp;

	if (fabs(cam.x) < EPSILON && fabs(cam.z) < EPSILON)
		up = vec3(0, 0, 1);
	else
		up = vec3(0, 1, 0);
	scene->viewport.origin = scene->camera.coor;
	scene->viewport.horizontal = vunit(vouter(cam, up));
	scene->viewport.vertical = vunit(vouter(scene->viewport.horizontal, cam));
	scene->viewport.focal_len = WIDTH / 2 / get_tan(scene->camera.fov / 2);
	tmp = vplus(scene->viewport.origin, vscale(cam, scene->viewport.focal_len));
	tmp = vminus(tmp, vscale(scene->viewport.horizontal, WIDTH / 2));
	tmp = vminus(tmp, vscale(scene->viewport.vertical, HEIGHT / 2));
	scene->viewport.left_bottom = tmp;
}

void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "miniRT");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img.addr = mlx_get_data_addr(
			scene->img.img,
			&scene->img.bits_per_pixel,
			&scene->img.size_line,
			&scene->img.endian);
}

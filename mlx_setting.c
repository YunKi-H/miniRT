/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:25:14 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:25:37 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_minirt(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	mlx_destroy_window(scene->mlx, scene->win);
	exit(0);
	return (0);
}

int	key_press(int key_code, t_scene *scene)
{
	if (key_code == KEY_ESC)
		exit_minirt(scene);
	return (0);
}

void	mlx_set_exit(t_scene *scene)
{
	mlx_key_hook(scene->win, &key_press, scene);
	mlx_hook(scene->win, KEY_EXIT, 0, &exit_minirt, scene);
}

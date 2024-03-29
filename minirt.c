/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:10:04 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:36:58 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	if (argc != 2 || \
	!ft_strrchr(argv[1], '.') || \
	ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", -1))
		ft_error("USAGE : \"./miniRT [MAP.rt]\"\n", 1);
	scene = init_scene(argv[1]);
	draw_scene(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
	mlx_set_exit(scene);
	mlx_loop(scene->mlx);
	return (0);
}

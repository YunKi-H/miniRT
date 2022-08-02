/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:19:02 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:21:41 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_element(const char *file, t_scene *scene)
{
	const int	fd = open(file, O_RDONLY);
	char		*line;
	int			idx_newline;

	if (fd == -1)
		ft_error("No such file or directory\n", 2);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		idx_newline = ft_strlen(line) - 1;
		if (line[idx_newline] == '\n')
			line[idx_newline] = '\0';
		read_element(line, scene);
		free(line);
	}
	close(fd);
	check_environment(scene->environment);
}

void	check_environment(int flag)
{
	if ((flag & AMBIENT) == 0)
		ft_error("THERE IS NO AMBIENT\n", 1);
	if ((flag & CAMERA) == 0)
		ft_error("THERE IS NO CAMERA\n", 1);
	if ((flag & LIGHT) == 0)
		ft_error("THERE IS NO LIGHT\n", 1);
}

void	read_element(char *line, t_scene *scene)
{
	char	**element;

	element = ft_split(line, ' ');
	if (!element[0])
		;
	else if (!ft_strncmp(element[0], "A", -1))
		read_ambient(element, scene);
	else if (!ft_strncmp(element[0], "C", -1))
		read_camera(element, scene);
	else if (!ft_strncmp(element[0], "L", -1))
		read_light(element, scene);
	else if (!ft_strncmp(element[0], "sp", -1))
		read_sphere(element, scene);
	else if (!ft_strncmp(element[0], "pl", -1))
		read_plane(element, scene);
	else if (!ft_strncmp(element[0], "cy", -1))
		read_cylinder(element, scene);
	else
		ft_error("WRONG Argument identifier\n", 1);
	free_split(element);
}

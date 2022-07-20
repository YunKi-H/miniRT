/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:21:23 by yuhwang           #+#    #+#             */
/*   Updated: 2022/07/21 03:34:12 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

static void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static void	ft_memo(char **note, char *buf, int fd)
{
	char	*tmp;
	ssize_t	len;

	len = BUFFER_SIZE + 1;
	while (!ft_strchr(note[fd], '\n') && !(len < BUFFER_SIZE))
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len <= 0)
			break ;
		buf[len] = '\0';
		tmp = ft_strjoin(note[fd], buf);
		ft_free((void **)&note[fd]);
		note[fd] = tmp;
	}
}

static char	*get_line(char **note, char *index, int fd)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (index)
	{
		line = ft_substr(note[fd], 0, index - note[fd] + 1);
		tmp = ft_strdup(index + 1);
		ft_free((void **)&note[fd]);
		note[fd] = tmp;
	}
	else if (!index && note[fd][0])
	{
		line = ft_strdup(note[fd]);
		ft_free((void **)&note[fd]);
	}
	else
		ft_free((void **)&note[fd]);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*note[FD_MAX];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > FD_MAX)
		return (NULL);
	if (!note[fd])
		note[fd] = ft_strdup("");
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ft_memo(note, buf, fd);
	free(buf);
	return (get_line(note, ft_strchr(note[fd], '\n'), fd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:51:55 by yuhwang           #+#    #+#             */
/*   Updated: 2021/11/26 12:44:07 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	char	tc;

	tmp = (char *)s;
	tc = (char)c;
	if (*tmp == tc)
		return (tmp);
	while (*tmp++)
	{
		if (*tmp == tc)
			return (tmp);
	}
	return (NULL);
}

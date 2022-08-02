/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:07:49 by yuhwang           #+#    #+#             */
/*   Updated: 2021/11/29 17:15:52 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp;
	char		tc;

	tmp = NULL;
	tc = (char)c;
	if (*s == tc)
		tmp = s;
	while (*s++)
	{
		if (*s == tc)
			tmp = s;
	}
	return ((char *)tmp);
}

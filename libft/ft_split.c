/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:27:45 by yuhwang           #+#    #+#             */
/*   Updated: 2021/11/26 12:44:04 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_freearr(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static int	ft_wdcount(char const *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (s[index])
	{
		while (s[index] == c)
			index++;
		if (s[index] != c && s[index])
		{
			while (s[index] != c && s[index])
				index++;
			count++;
		}
	}
	return (count);
}

static int	ft_wdlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wdcount;
	int		wdlen;

	result = (char **)malloc(sizeof(char *) * (ft_wdcount(s, c) + 1));
	if (!result)
		return (NULL);
	wdcount = 0;
	while (*s)
	{
		wdlen = 0;
		if (*s != c)
		{
			wdlen = ft_wdlen(s, c);
			result[wdcount] = (char *)malloc(sizeof(char) * (wdlen + 1));
			if (!result[wdcount])
				return (ft_freearr(result, wdcount));
			ft_strlcpy(result[wdcount++], s, wdlen + 1);
		}
		s += wdlen;
		if (*s)
			s++;
	}
	result[wdcount] = NULL;
	return (result);
}

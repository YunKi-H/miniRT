/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:21:38 by yuhwang           #+#    #+#             */
/*   Updated: 2021/11/26 12:42:52 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digitlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr(char *ret, int n, size_t len)
{
	ret[len] = '\0';
	if (n == 0)
		ret[--len] = '0';
	else if (n > 0)
	{
		while (n != 0)
		{
			ret[--len] = n % 10 + '0';
			n /= 10;
		}
	}
	else
	{
		while (n != 0)
		{
			ret[--len] = -1 * (n % 10) + '0';
			n /= 10;
		}
		ret[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	size_t	len;

	len = ft_digitlen(n);
	if (n < 0)
		len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_putnbr(ret, n, len);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:56:37 by yuhwang           #+#    #+#             */
/*   Updated: 2021/11/26 12:43:52 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_fd(int n, int fd)
{
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		return ;
	}
	else
	{
		ft_itoa_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = n;
	if (i == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (i >= 0)
	{
		ft_itoa_fd(i, fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		i = -i;
		ft_itoa_fd(i, fd);
	}
}

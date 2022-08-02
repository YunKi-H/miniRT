/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boolean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:23:12 by yuhwang           #+#    #+#             */
/*   Updated: 2022/08/02 14:23:43 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_isdouble(char *str)
{
	int	point;

	point = 0;
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.')
			return (FALSE);
		if (*str == '.')
			point += 1;
		if (*str == '.' && point > 1)
			return (FALSE);
		str += 1;
	}
	return (TRUE);
}

int	ft_isint(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (FALSE);
	}
	return (TRUE);
}

int	ft_isrgb(double color)
{
	return (color >= 0.0 && color < 256.0);
}

int	ft_isunit(double xyz)
{
	return (xyz >= -1.0 && xyz <= 1.0);
}

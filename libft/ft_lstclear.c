/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:43:03 by yuhwang           #+#    #+#             */
/*   Updated: 2021/11/26 20:24:41 by yuhwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now;
	t_list	*tmp;

	now = *lst;
	if (lst == 0 || del == 0)
		return ;
	while (now)
	{
		tmp = now;
		now = now -> next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}

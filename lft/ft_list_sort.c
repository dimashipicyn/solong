/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:11:24 by lbespin           #+#    #+#             */
/*   Updated: 2020/08/05 21:59:35 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	void	*tmp;
	int		flag;
	t_list	*list;

	list = *begin_list;
	while (1 && list)
	{
		flag = 1;
		while (list->next)
		{
			if ((*cmp)(list->content, list->next->content) > 0)
			{
				tmp = list->content;
				list->content = list->next->content;
				list->next->content = tmp;
				flag = 0;
			}
			list = list->next;
		}
		if (flag)
			return ;
		list = *begin_list;
	}
}

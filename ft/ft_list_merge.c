/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:50:56 by lbespin           #+#    #+#             */
/*   Updated: 2021/01/24 14:27:13 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list	*tmp;

	tmp = *begin_list1;
	if (!begin_list2)
		return ;
	if (!tmp)
	{
		*begin_list1 = begin_list2;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = begin_list2;
}

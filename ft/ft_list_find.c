/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:05:55 by lbespin           #+#    #+#             */
/*   Updated: 2021/01/24 14:23:11 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
	if (!data_ref || !cmp)
		return (0);
	while (begin_list)
	{
		if ((*cmp)(data_ref, begin_list->content) == 0)
			return (begin_list);
		begin_list = begin_list->next;
	}
	return (0);
}

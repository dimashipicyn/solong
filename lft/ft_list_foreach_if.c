/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:20:33 by lbespin           #+#    #+#             */
/*   Updated: 2021/01/24 14:25:01 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
		void *data_ref, int (*cmp)(void *, void *))
{
	if (!f || !data_ref || !cmp)
		return ;
	while (begin_list)
	{
		if ((*cmp)(begin_list->content, data_ref) == 0)
			(*f)(begin_list->content);
		begin_list = begin_list->next;
	}
}

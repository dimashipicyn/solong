/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:37:16 by lbespin           #+#    #+#             */
/*   Updated: 2020/08/04 19:48:14 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*prev;
	t_list	*tmp;
	t_list	*list;

	if (!data_ref || !cmp || !*begin_list)
		return ;
	prev = NULL;
	list = *begin_list;
	while (list)
	{
		if ((*cmp)(data_ref, list->content) == 0)
		{
			tmp = list;
			if (!prev)
				*begin_list = list->next;
			else
				prev->next = list->next;
			free(tmp);
		}
		else
			prev = list;
		list = list->next;
	}
}

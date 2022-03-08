/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 21:41:00 by lbespin           #+#    #+#             */
/*   Updated: 2020/08/04 23:44:11 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_reverse_fun(t_list *begin_list)
{
	t_list	*left;
	t_list	*right;
	int		top;
	int		size;
	void	*data;

	size = ft_list_size(begin_list);
	left = begin_list;
	top = 0;
	while (top++ < size--)
	{
		right = ft_list_at(begin_list, size);
		data = left->data;
		left->data = right->data;
		right->data = data;
		left = left->next;
	}
}

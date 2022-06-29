/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:19:41 by lbespin           #+#    #+#             */
/*   Updated: 2021/01/24 14:28:56 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_push_back(t_list **begin_list, void *data)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *begin_list;
	if (!tmp)
	{
		tmp = ft_create_elem(data);
		if (!tmp)
			return ;
		*begin_list = tmp;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	next = ft_create_elem(data);
	if (!next)
		return ;
	tmp->next = next;
}

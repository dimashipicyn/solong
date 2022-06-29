/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:46:33 by lbespin           #+#    #+#             */
/*   Updated: 2021/01/24 14:23:53 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	if (!f)
		return ;
	while (begin_list)
	{
		(*f)(begin_list->content);
		begin_list = begin_list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:40:08 by lbespin           #+#    #+#             */
/*   Updated: 2021/01/24 14:20:34 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	while (nbr-- > 0 && begin_list)
		begin_list = begin_list->next;
	return (begin_list);
}

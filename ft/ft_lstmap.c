/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:40:50 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/04 18:38:48 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	new = 0;
	if (f)
	{
		tmp = 0;
		while (lst)
		{
			tmp = ft_lstnew((*f)(lst->content));
			if (tmp)
				ft_lstadd_back(&new, tmp);
			else
			{
				ft_lstclear(&new, del);
				return (0);
			}
			lst = lst->next;
		}
	}
	return (new);
}

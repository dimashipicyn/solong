/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:18:48 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/04 17:27:48 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*free_lst;

	if (lst && del)
	{
		free_lst = *lst;
		while (free_lst)
		{
			*lst = (*lst)->next;
			(*del)(free_lst->content);
			free(free_lst);
			free_lst = *lst;
		}
		*lst = 0;
	}
}

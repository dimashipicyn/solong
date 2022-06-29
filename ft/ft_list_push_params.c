/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:05:50 by lbespin           #+#    #+#             */
/*   Updated: 2020/08/05 21:53:26 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_push_params(int ac, char **av)
{
	t_list		*result;
	t_list		*tmp;
	int			i;

	i = 0;
	result = 0;
	while (i < ac)
	{
		tmp = result;
		result = ft_create_elem(av[i++]);
		result->next = tmp;
	}
	return (result);
}

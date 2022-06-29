/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:07:03 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:07:06 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memptr, int val, size_t n)
{
	const char		*tmp;
	char			ch;
	size_t			i;

	tmp = (const char *)memptr;
	ch = (char)val;
	i = 0;
	while (i < n)
	{
		if (tmp[i] == ch)
			return ((void *)&tmp[i]);
		i++;
	}
	return ((void *)0);
}

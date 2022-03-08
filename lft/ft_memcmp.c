/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:07:16 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:14:48 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *memptr1, const void *memptr2, size_t n)
{
	const unsigned char		*ptr_1;
	const unsigned char		*ptr_2;
	size_t					i;

	ptr_1 = (const unsigned char *)memptr1;
	ptr_2 = (const unsigned char *)memptr2;
	i = 0;
	while (i < n)
	{
		if (ptr_1[i] != ptr_2[i])
			return (ptr_1[i] - ptr_2[i]);
		i++;
	}
	return (0);
}

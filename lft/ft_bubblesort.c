/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubblesort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:01:19 by lbespin           #+#    #+#             */
/*   Updated: 2021/02/24 19:03:59 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bubblesort(void *array, int size, int len,
int (*cmp)(void *, void *))
{
	int	max;
	int	i;
	int	issort;

	max = size * len - size;
	issort = 0;
	while (!issort)
	{
		i = 0;
		issort = 1;
		while (i < max)
		{
			if (cmp(array + i, array + i + size) > 0)
			{
				issort = 0;
				ft_swap(array + i, array + i + size, size);
			}
			i += size;
		}
	}
}

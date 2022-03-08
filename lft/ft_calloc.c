/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:02:12 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:02:15 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmem, size_t size)
{
	size_t	n;
	void	*memory;

	n = 0;
	n = nmem * size;
	memory = 0;
	memory = malloc(n);
	if (memory)
		ft_bzero(memory, n);
	return (memory);
}

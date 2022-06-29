/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:59:58 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:01:58 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *memptr, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)memptr;
	i = 0;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}

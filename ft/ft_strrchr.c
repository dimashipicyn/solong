/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:12:25 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:12:27 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int val)
{
	char	*tmp;
	char	c;

	tmp = (char *)0;
	while (1)
	{
		c = *str;
		if (c == val)
			tmp = (char *)str;
		if (c == '\0')
			break ;
		str++;
	}
	return (tmp);
}

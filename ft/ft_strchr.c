/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:10:06 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:10:08 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int val)
{
	size_t			i;
	char			tmp;

	i = 0;
	tmp = (char)val;
	while (1)
	{
		if (str[i] == tmp)
			return ((char *)&str[i]);
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

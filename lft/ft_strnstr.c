/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:12:10 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/06 17:06:40 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i] == s2[j])
		{
			i++;
			j++;
			if (i <= n && s2[j] == '\0')
				return ((char *)&s1[i - j]);
		}
		if (j == 0)
			i++;
		else
			i = (i - j) + 1;
	}
	return ((char *)0);
}

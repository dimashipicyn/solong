/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:11:57 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:12:01 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	char		*s1_ptr;
	char		*s2_ptr;

	s1_ptr = (char *)s1;
	s2_ptr = (char *)s2;
	i = 0;
	if (n == (size_t)0)
		return (0);
	while (i < n && *s1_ptr)
	{
		if (*s1_ptr != *s2_ptr)
			break ;
		i++;
		s1_ptr++;
		s2_ptr++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)*s1_ptr - (unsigned char)*s2_ptr);
}

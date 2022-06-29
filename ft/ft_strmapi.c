/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:11:34 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:11:36 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char	*str;
	int		n;
	int		pos;

	if (!s || !f)
		return (0);
	n = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str)
	{
		pos = 0;
		while (pos < n)
		{
			str[pos] = (*f)(pos, s[pos]);
			pos++;
		}
		str[pos] = '\0';
		return (str);
	}
	return (0);
}

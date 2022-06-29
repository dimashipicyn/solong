/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:13:10 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:13:11 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	pos;

	pos = 0;
	if (!s)
		return (0);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res)
	{
		if (start <= ft_strlen(s))
		{
			while (pos < len && s[start])
			{
				res[pos] = s[start];
				pos++;
				start++;
			}
		}
		res[pos] = '\0';
		return (res);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:10:33 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 14:39:46 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s;
	unsigned int	n;

	if (!s1 || !s2)
		return (0);
	n = ft_strlen(s1);
	n += ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (n + 1));
	if (s)
	{
		ft_strlcpy(s, s1, ft_strlen(s1) + 1);
		ft_strlcat(s, s2, n + 1);
		return (s);
	}
	return (0);
}

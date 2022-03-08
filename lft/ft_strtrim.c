/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:12:48 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 17:56:21 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		s1_pos;
	size_t		max_pos;

	if (!s1 || !set)
		return (0);
	s1_pos = ft_strlen(s1);
	while (s1_pos > 0 && ft_strchr(set, s1[s1_pos]))
		s1_pos--;
	max_pos = s1_pos;
	s1_pos = 0;
	while (s1[s1_pos] && ft_strchr(set, s1[s1_pos]))
		s1_pos++;
	if (max_pos < s1_pos)
		max_pos = 0;
	else
		max_pos -= s1_pos;
	str = (char *)malloc(sizeof(char) * max_pos + 2);
	if (str)
	{
		ft_strlcpy(str, s1 + s1_pos, max_pos + 2);
		return (str);
	}
	return (0);
}

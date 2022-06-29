/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:12:37 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:12:38 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		k;
	char	tmp;

	k = 0;
	i = ft_strlen(str);
	while (k < i)
	{
		tmp = str[k];
		str[k] = str[i - 1];
		str[i - 1] = tmp;
		i--;
		k++;
	}
	return (str);
}

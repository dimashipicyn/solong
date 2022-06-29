/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:04:17 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:06:17 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse(long long int n, char *str)
{
	int			pos;

	pos = 0;
	if (n < 0)
		n = -n;
	while (1)
	{
		str[pos++] = n % 10 + '0';
		n = n / 10;
		if (n == 0)
			break ;
	}
	return (pos);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	tmp[50];
	int		pos;

	pos = parse(n, tmp);
	if (n < 0)
		tmp[pos++] = '-';
	tmp[pos] = '\0';
	str = ft_strdup(tmp);
	if (str)
		return (ft_strrev(str));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:59:19 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 18:17:57 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	ft_str_to_nb(char *str, int sign)
{
	int				i;
	unsigned long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > (unsigned long)9223372036854775807)
		{
			if (sign)
				result = (unsigned long)9223372036854775807 + 1;
			else
				result = (unsigned long)9223372036854775807;
			return (result);
		}
	}
	return (result);
}

int	ft_atoi(char *str)
{
	unsigned long	result;
	int				i;
	int				sign;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		sign = 1;
	else
		sign = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	result = ft_str_to_nb(&str[i], sign);
	if (sign > 0)
		result = -result;
	return ((int)result);
}

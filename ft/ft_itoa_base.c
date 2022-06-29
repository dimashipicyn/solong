/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:27:18 by lbespin           #+#    #+#             */
/*   Updated: 2020/12/07 18:27:49 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned long long nb, int base)
{
	char	*hex;
	char	buf[50];
	int		i;
	int		n;

	if (nb == 0)
		return (ft_strdup("0"));
	hex = "0123456789abcdef";
	i = 0;
	n = 0;
	while (nb > 0)
	{
		n = nb % base;
		buf[i++] = hex[n];
		nb = nb / base;
	}
	buf[i] = '\0';
	ft_strrev(buf);
	return (ft_strdup(buf));
}

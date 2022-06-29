/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:08:24 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:21:04 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int			i;
	long long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		write(fd, "-", 1);
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		i = nbr % 10 + '0';
	}
	else
		i = nbr + '0';
	write(fd, &i, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_repeat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:19:36 by lbespin           #+#    #+#             */
/*   Updated: 2020/12/12 12:22:13 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_repeat(int repeat, char *str)
{
	int	i;

	i = 0;
	if (repeat > 0)
	{
		while (repeat > i++)
			write(1, str, ft_strlen(str));
		return (repeat);
	}
	return (0);
}

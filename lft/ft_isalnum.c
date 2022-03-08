/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:02:37 by lbespin           #+#    #+#             */
/*   Updated: 2020/11/03 13:02:45 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int character)
{
	if (character >= 'a' && character <= 'z')
		return (1);
	if (character >= 'A' && character <= 'Z')
		return (1);
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}

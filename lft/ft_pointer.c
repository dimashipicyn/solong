/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:21:57 by lbespin           #+#    #+#             */
/*   Updated: 2021/02/24 19:10:33 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	ft_print_zero(t_flag *params, char *buf, int len)
{
	int		precision;

	precision = params->precision;
	while (precision-- > len)
	{
		params->err = write(1, "0", 1);
		params->res += 1;
	}
	while (*buf)
	{
		params->err = write(1, buf++, 1);
		params->res += 1;
	}
	while ((params->width)-- > params->precision + 2)
	{
		params->err = write(1, " ", 1);
		params->res += 1;
	}
}

static void	ft_pointer(t_flag *params, char *buf)
{
	int		len;

	if (buf[0] == '0' && params->precision == 0)
		buf[0] = '\0';
	len = ft_strlen(buf);
	if (params->precision < len)
		params->precision = len;
	if (!(params->flags & LEFT))
	{
		while ((params->width)-- > params->precision + 2)
		{
			params->err = write(1, " ", 1);
			params->res += 1;
		}
	}
	params->err = write(1, "0x", 2);
	params->res += 2;
	ft_print_zero(params, buf, len);
}

void	ft_print_p(t_flag *params)
{
	char	*buf;

	if (*(params->fmt) == 'p')
	{
		buf = ft_itoa_base((unsigned long long)va_arg(params->arg, void *), 16);
		if (!buf)
		{
			params->err = -1;
			return ;
		}
		ft_pointer(params, buf);
		free(buf);
		(params->fmt)++;
	}
}

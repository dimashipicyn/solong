/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:54:18 by lbespin           #+#    #+#             */
/*   Updated: 2021/02/24 19:11:39 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	ft_number(t_flag *params, char ch, char *buf, int sign)
{
	int		len;
	char	str[2];

	str[0] = ch;
	if (buf[0] == '0' && params->precision == 0)
		buf[0] = '\0';
	len = ft_strlen(buf);
	if (params->precision < len)
		params->precision = len;
	if (!(params->flags & LEFT))
	{
		if (sign && ch == '0')
		{
			params->err = write(1, "-", 1);
			sign = 0;
		}
		params->res += ft_str_repeat(params->width - params->precision, str);
		params->width = -1;
	}
	if (sign)
		params->err = write(1, "-", 1);
	params->res += ft_str_repeat(params->precision - len, "0");
	params->err = write(1, buf, len);
	params->res += len;
	params->res += ft_str_repeat(params->width - params->precision, " ");
}

void	ft_print_d(t_flag *params)
{
	char		*buf;
	char		ch;
	long long	nb;
	int			sign;

	if (params->flags & ZEROPAD)
		ch = '0';
	else
		ch = ' ';
	if (*(params->fmt) == 'd' || *(params->fmt) == 'i')
	{
		sign = 0;
		nb = va_arg(params->arg, int);
		if (nb < 0)
		{
			nb = -nb;
			sign = 1;
			params->width--;
			params->res++;
		}
		buf = ft_itoa_base(nb, 10);
		if (!buf)
		{
			params->err = -1;
			return ;
		}
		ft_number(params, ch, buf, sign);
		free(buf);
		(params->fmt)++;
	}
}

void	ft_print_u(t_flag *params)
{
	char	*buf;
	char	ch;

	if (params->flags & ZEROPAD)
		ch = '0';
	else
		ch = ' ';
	if (*(params->fmt) == 'u')
	{
		buf = ft_itoa_base(va_arg(params->arg, unsigned int), 10);
		if (!buf)
		{
			params->err = -1;
			return ;
		}
		ft_number(params, ch, buf, 0);
		free(buf);
		(params->fmt)++;
	}
}

int	ft_print_x(t_flag *params)
{
	char	*buf;
	char	ch;

	if (params->flags & ZEROPAD)
		ch = '0';
	else
		ch = ' ';
	if (*(params->fmt) == 'x' || *(params->fmt) == 'X')
	{
		buf = ft_itoa_base((unsigned int)va_arg(params->arg, void *), 16);
		if (!buf)
		{
			params->err = -1;
			return (0);
		}
		if (*(params->fmt) == 'X')
			ft_toupper_str(buf);
		ft_number(params, ch, buf, 0);
		free(buf);
		(params->fmt)++;
	}
	else if (*(params->fmt) == '%')
	{
		buf = "%";
		ft_number(params, ch, buf, 0);
		(params->fmt)++;
		return (1);
	}
	return (0);
}

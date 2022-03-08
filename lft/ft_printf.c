/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:03:31 by lbespin           #+#    #+#             */
/*   Updated: 2021/02/24 19:09:24 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	ft_print(t_flag *params)
{
	while (*(params->fmt))
	{
		if (*(params->fmt) == '%')
			break ;
		params->err = write(1, params->fmt, 1);
		params->res += 1;
		(params->fmt)++;
	}
	if (*(params->fmt) == '%')
		(params->fmt)++;
}

static void	ft_init_params(t_flag *params)
{
	params->flags = 0;
	params->width = -1;
	params->precision = -1;
}

static int	ft_processing(t_flag *params)
{
	while (*(params->fmt))
	{
		ft_init_params(params);
		ft_print(params);
		if (*(params->fmt) == '\0')
			break ;
		ft_parser(params);
		if (ft_print_x(params))
			continue ;
		ft_print_c(params);
		ft_print_s(params);
		ft_print_p(params);
		ft_print_d(params);
		ft_print_u(params);
		if (params->err == -1)
			return (-1);
	}
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	t_flag		params;

	va_start(params.arg, fmt);
	params.fmt = (char *)fmt;
	params.res = 0;
	params.err = 0;
	ft_init_params(&params);
	if (ft_processing(&params) == -1)
		return (-1);
	va_end(params.arg);
	return (params.res);
}

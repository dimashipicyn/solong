/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:16:15 by lbespin           #+#    #+#             */
/*   Updated: 2021/02/24 19:10:08 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_flags(t_flag *params)
{
	while (*(params->fmt))
	{
		if (*(params->fmt) == '-')
			params->flags |= LEFT;
		else if (*(params->fmt) == '0')
			params->flags |= ZEROPAD;
		else
			break ;
		(params->fmt)++;
	}
}

void	ft_width(t_flag *params)
{
	if (ft_isdigit(*(params->fmt)))
	{
		params->width = 0;
		while (ft_isdigit(*(params->fmt)))
		{
			params->width = params->width * 10 + (*(params->fmt) - '0');
			(params->fmt)++;
		}
	}
	if (*(params->fmt) == '*')
	{
		(params->fmt)++;
		params->width = va_arg(params->arg, int);
		if (params->width < 0)
		{
			params->width = -(params->width);
			params->flags |= LEFT;
		}
	}
}

void	ft_precision(t_flag *params)
{
	if (*(params->fmt) == '.')
	{
		(params->fmt)++;
		params->precision = 0;
		while (ft_isdigit(*(params->fmt)))
		{
			params->precision = params->precision * 10 + (*(params->fmt) - '0');
			(params->fmt)++;
		}
		if (*(params->fmt) == '*')
		{
			(params->fmt)++;
			params->precision = va_arg(params->arg, int);
			if (params->precision < 0)
			{
				params->precision = -1;
				return ;
			}
		}
		params->flags &= ~ZEROPAD;
	}
}

void	ft_parser(t_flag *params)
{
	ft_flags(params);
	ft_width(params);
	ft_precision(params);
	return ;
}

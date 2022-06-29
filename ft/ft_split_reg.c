/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_reg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:33:03 by lbespin           #+#    #+#             */
/*   Updated: 2021/02/18 18:37:07 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*next_word(char *s, char *reg)
{
	while (*s)
	{
		if (ft_strchr(reg, *(s + 1)) && !ft_strchr(reg, *s))
			return (s + 1);
		s++;
	}
	return (0);
}

static int	word_counter(char *s, char *reg)
{
	int	n;

	n = 0;
	while (*s)
	{
		s = next_word(s, reg);
		if (s)
			n++;
		else
			break ;
	}
	return (n);
}

static void	new_split(char **new, char *s, char *reg)
{
	char	*tmp;
	int		n;

	n = 0;
	while (*s)
	{
		if (ft_strchr(reg, *s))
		{
			s++;
			continue ;
		}
		tmp = next_word(s, reg);
		if (tmp)
		{
			new[n++] = ft_substr(s, 0, tmp - s);
			s = tmp;
		}
		else
			break ;
	}
	new[n] = NULL;
}

char	**ft_split_reg(char *s, char *reg)
{
	char	**new;
	int		n;

	n = word_counter(s, reg);
	if (n == 0)
		return (0);
	new = (char **)malloc(sizeof(char *) * (n + 1));
	if (!new)
		return (0);
	new_split(new, s, reg);
	return (new);
}

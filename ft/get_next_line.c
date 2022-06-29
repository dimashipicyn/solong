/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:51:06 by lbespin           #+#    #+#             */
/*   Updated: 2021/03/23 08:12:17 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1024

static int	ft_check_newline(char *buf)
{
	int	i;

	i = 0;
	if (buf)
	{
		while (buf[i])
		{
			if (buf[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

static char	*ft_strdup_(char *s)
{
	if (!s)
		return (0);
	return (ft_strdup(s));
}

static char	*ft_newline(char **thread)
{
	char	*new;
	char	*tmp;
	int		n;

	new = 0;
	n = ft_check_newline(*thread);
	if (n >= 0)
		new = (char *)ft_calloc(n + 1, sizeof(char));
	if (new)
	{
		ft_memcpy(new, *thread, n);
		tmp = ft_strdup(*thread + n + 1);
		if (!tmp)
			tmp = ft_strdup("");
		free(*thread);
		*thread = tmp;
	}
	else
	{
		new = ft_strdup_(*thread);
		if (!new)
			new = ft_strdup("");
		free(*thread);
		*thread = 0;
	}
	return (new);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE];
	static char	*thread[1025];
	char		*new;
	int			n;

	if (fd < 0 || !line)
		return (-1);
	n = 0;
	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		buf[n] = '\0';
		if (thread[fd] == 0)
			thread[fd] = ft_strdup("");
		new = ft_strjoin(thread[fd], buf);
		free(thread[fd]);
		thread[fd] = new;
		if (ft_check_newline(buf) >= 0)
			break ;
	}
	*line = ft_newline(&thread[fd]);
	if (n < 0 || *line == 0)
		return (-1);
	if (!thread[fd] && n == 0)
		return (0);
	return (1);
}

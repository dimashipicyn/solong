#include "utils.h"
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

static int	check_newline(char *buf)
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

static char	*strdup_(char *s)
{
	if (!s)
		return (0);
	return (strdup(s));
}

static char	*newline(char **thread)
{
	char	*new;
	char	*tmp;
	int		n;

	new = 0;
	n = check_newline(*thread);
	if (n >= 0)
		new = (char *)calloc(n + 1, sizeof(char));
	if (new)
	{
		memcpy(new, *thread, n);
		tmp = strdup(*thread + n + 1);
		if (!tmp)
			tmp = strdup("");
		free(*thread);
		*thread = tmp;
	}
	else
	{
		new = strdup_(*thread);
		if (!new)
			new = strdup("");
		free(*thread);
		*thread = 0;
	}
	return (new);
}

static char *join(const char* s1, const char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1);

    if (result) // thanks @pmg
    {
        strcpy(result, s1);
        strcat(result, s2);
    }

    return result;
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
			thread[fd] = strdup("");
		new = join(thread[fd], buf);
		free(thread[fd]);
		thread[fd] = new;
		if (check_newline(buf) >= 0)
			break ;
	}
	*line = newline(&thread[fd]);
	if (n < 0 || *line == 0)
		return (-1);
	if (!thread[fd] && n == 0)
		return (0);
	return (1);
}

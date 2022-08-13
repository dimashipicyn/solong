#include "utils.h"
#include <ctype.h>

int	ut_isdigit_str(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

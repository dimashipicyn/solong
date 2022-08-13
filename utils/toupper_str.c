#include "utils.h"
#include <ctype.h>

void	ut_toupper_str(char *str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}

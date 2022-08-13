#include "utils.h"
#include <string.h>

char	*ut_strrev(char *str)
{
	int		i;
	int		k;
	char	tmp;

	k = 0;
	i = strlen(str);
	while (k < i)
	{
		tmp = str[k];
		str[k] = str[i - 1];
		str[i - 1] = tmp;
		i--;
		k++;
	}
	return (str);
}

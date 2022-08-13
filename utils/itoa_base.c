#include "utils.h"

int ut_itoa_base(char buf[], int64_t nbr, int base)
{
	char	*hex;
	int		i;
	int		n;

	hex = "0123456789abcdef";

	if (nbr == 0) {
		buf[0] = hex[0];
		buf[1] = '\0';
	}

	i = 0;
	n = 0;
	while (nbr > 0)
	{
		n = nbr % base;
		buf[i++] = hex[n];
		nbr = nbr / base;
	}
	buf[i] = '\0';
	ut_strrev(buf);
	return 0;
}

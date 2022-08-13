#include "utils.h"
#include <string.h>

void	ut_swap(void *a, void *b, int size)
{
	char	t[100];

	memmove(t, a, size);
	memmove(a, b, size);
	memmove(b, t, size);
}

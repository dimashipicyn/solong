#include "utils.h"

void	ut_bubblesort(void *_array, int size, int len, int (*cmp)(void *, void *))
{
	int	max;
	int	i;
	int	issort;
	unsigned char* array = _array;

	max = size * len - size;
	issort = 0;
	while (!issort)
	{
		i = 0;
		issort = 1;
		while (i < max)
		{
			if (cmp(array + i, array + i + size) > 0)
			{
				issort = 0;
				ut_swap(array + i, array + i + size, size);
			}
			i += size;
		}
	}
}

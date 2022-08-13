#include "utils.h"

t_list	*ut_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
	if (!data_ref || !cmp)
		return (0);
	while (begin_list)
	{
		if ((*cmp)(data_ref, begin_list->content) == 0)
			return (begin_list);
		begin_list = begin_list->next;
	}
	return (0);
}

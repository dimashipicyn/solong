#include "utils.h"

void	ut_list_foreach_if(t_list *begin_list, void (*f)(void *),
		void *data_ref, int (*cmp)(void *, void *))
{
	if (!f || !data_ref || !cmp)
		return ;
	while (begin_list)
	{
		if ((*cmp)(begin_list->content, data_ref) == 0)
			(*f)(begin_list->content);
		begin_list = begin_list->next;
	}
}

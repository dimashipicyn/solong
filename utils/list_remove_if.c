#include "utils.h"
#include <stdlib.h>

void	ut_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*prev;
	t_list	*tmp;
	t_list	*list;

	if (!data_ref || !cmp || !*begin_list)
		return ;
	prev = NULL;
	list = *begin_list;
	while (list)
	{
		if ((*cmp)(data_ref, list->content) == 0)
		{
			tmp = list;
			list = list->next;
			if (!prev)
				*begin_list = list;
			else
				prev->next = list;
			free(tmp);
		}
		else {
			prev = list;
			list = list->next;
		}
	}
}

#include "utils.h"

void	ut_list_foreach(t_list *begin_list, void (*f)(void *))
{
	if (!f)
		return ;
	while (begin_list)
	{
		(*f)(begin_list->content);
		begin_list = begin_list->next;
	}
}

#include "utils.h"

void	ut_list_push_front(t_list **begin_list, void *data)
{
	t_list	*tmp;

	tmp = ut_create_elem(data);
	if (!tmp)
		return ;
	tmp->next = *begin_list;
	*begin_list = tmp;
}

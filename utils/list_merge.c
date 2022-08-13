#include "utils.h"

void	ut_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list	*tmp;

	tmp = *begin_list1;
	if (!begin_list2)
		return ;
	if (!tmp)
	{
		*begin_list1 = begin_list2;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = begin_list2;
}

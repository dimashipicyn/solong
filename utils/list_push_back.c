#include "utils.h"

void	ut_list_push_back(t_list **begin_list, void *data)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *begin_list;
	if (!tmp)
	{
		tmp = ut_create_elem(data);
		if (!tmp)
			return ;
		*begin_list = tmp;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	next = ut_create_elem(data);
	if (!next)
		return ;
	tmp->next = next;
}

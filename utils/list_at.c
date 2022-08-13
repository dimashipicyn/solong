#include "utils.h"

t_list	*ut_list_at(t_list *begin_list, unsigned int nbr)
{
	while (nbr-- > 0 && begin_list)
		begin_list = begin_list->next;
	return (begin_list);
}

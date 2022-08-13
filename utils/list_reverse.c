#include "utils.h"

void	ut_list_reverse(t_list **begin_list)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;

	prev = 0;
	curr = *begin_list;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*begin_list = prev;
}

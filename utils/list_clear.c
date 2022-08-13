#include "utils.h"
#include <stdlib.h>

void	ut_list_clear(t_list **begin_list)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *begin_list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*begin_list = NULL;
}

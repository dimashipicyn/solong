#include "utils.h"
#include <stdlib.h>

t_list	*ut_create_elem(void *content)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	tmp->content = content;
	return (tmp);
}

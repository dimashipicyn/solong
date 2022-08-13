#include "utils.h"

void	ut_list_sort(t_list **begin_list, int (*cmp)())
{
	void	*tmp;
	int		flag;
	t_list	*list;

	list = *begin_list;
	while (1 && list)
	{
		flag = 1;
		while (list->next)
		{
			if ((*cmp)(list->content, list->next->content) > 0)
			{
				tmp = list->content;
				list->content = list->next->content;
				list->next->content = tmp;
				flag = 0;
			}
			list = list->next;
		}
		if (flag)
			return ;
		list = *begin_list;
	}
}

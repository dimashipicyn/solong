#include "utils.h"

t_list	*ut_list_push_params(int ac, char **av)
{
	t_list		*result;
	t_list		*tmp;
	int			i;

	i = 0;
	result = 0;
	while (i < ac)
	{
		tmp = result;
		result = ut_create_elem(av[i++]);
		result->next = tmp;
	}
	return (result);
}

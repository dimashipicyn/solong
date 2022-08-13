#ifndef UTILS_H
# define UTILS_H

#include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ut_create_elem(void *content);
t_list				*ut_list_at(t_list *begin_list, unsigned int nbr);
void				ut_list_clear(t_list **begin_list);
t_list				*ut_list_find(t_list *begin_list, void *data_ref, int (*cmp)(void*, void*));
void				ut_list_foreach_if(t_list *begin_list, void (*f)(void *),
						void *data_ref, int (*cmp)(void *, void *));
void				ut_list_foreach(t_list *begin_list, void (*f)(void *));
t_list				*ut_list_last(t_list *begin_list);
void				ut_list_merge(t_list **begin_list1, t_list *begin_list2);
void				ut_list_push_back(t_list **begin_list, void *data);
void				ut_list_push_front(t_list **begin_list, void *data);
t_list				*ut_list_push_params(int ac, char **av);
void				ut_list_remove_if(t_list **begin_list,
						void *data_ref, int (*cmp)(void*, void*));
void				ut_list_reverse_fun(t_list *begin_list);
void				ut_list_reverse(t_list **begin_list);
int					ut_list_size(t_list *begin_list);
void				ut_list_sort(t_list **begin_list, int (*cmp)());


char				*ut_strrev(char *str);
int					ut_itoa_base(char buf[], int64_t nb, int base);
void				ut_toupper_str(char *str);
int					get_next_line(int fd, char **line);
int					ut_isdigit_str(char *str);
void				ut_swap(void *a, void *b, int size);
void				ut_bubblesort(void *array, int size, int len,
						int (*cmp)(void *, void *));

int64_t get_time();

#endif

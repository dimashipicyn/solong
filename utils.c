#include "utils.h"
#include "libft.h"

#include <time.h>

typedef struct s_map
{
	t_list* list;
	int (*cmp)();
	void* (*alloc)();
	void (*dealloc)();
} t_map;

t_map* new_map(void* alloc_func, void* dealloc_func, void* cmp_func)
{
	t_map* map = ft_calloc(1 ,sizeof(t_map));

	map->list = NULL;
	map->alloc = alloc_func;
	map->cmp = cmp_func;
	map->dealloc = dealloc_func;
	return map;
}

void free_map(t_map* map)
{
	t_iter_map iter;
	for (init_iter_map(&iter, map); !iter_map_end(&iter); iter_map_next(&iter))
	{
		void* pair = iter_map_get(&iter);
		map->dealloc(pair);
	}
	ft_list_clear(&map->list);
	free(map);
}

void map_insert(t_map* map, void* key, void* value)
{
	t_list* found = ft_list_find(map->list, key, map->cmp);
	if (found) {
		map->dealloc(found->content);
		found->content = map->alloc(key, value);
	}
	else {
		ft_list_push_back(&map->list, map->alloc(key, value));
	}
}

void* map_find(t_map* map, void* key)
{
	t_list* found = ft_list_find(map->list, key, map->cmp);
	if (found) {
		return found->content;
	}
	return NULL;
}

void init_iter_map(t_iter_map* iter, t_map* map)
{
	iter->data = map->list;
}

void iter_map_next(t_iter_map* iter)
{
	iter->data = ((t_list*)iter->data)->next;
}

void* iter_map_get(t_iter_map* iter)
{
	return ((t_list*)iter->data)->content;
}

int iter_map_end(t_iter_map* iter)
{
	if (iter->data == NULL) {
		return 1;
	}
	return 0;
}

int64_t get_time()
{
	struct timespec tms;

    if (clock_gettime(CLOCK_REALTIME, &tms)) {
        return -1;
    }
    
    int64_t millisec = tms.tv_sec * 1000;

    millisec += tms.tv_nsec/1000000;

    if (tms.tv_nsec % 1000000 >= 500000) {
        ++millisec;
    }
	return millisec;
}
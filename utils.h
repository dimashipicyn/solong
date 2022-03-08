#ifndef UTILS_H
#define UTILS_H

typedef struct s_map t_map;
typedef struct s_iter_map
{
    void* data;
} t_iter_map;

t_map* new_map(void* alloc_func, void* dealloc_func, void* cmp_func);
void free_map(t_map* map);
void map_insert(t_map* map, void* key, void* value);
void* map_find(t_map* map, void* key);

void init_iter_map(t_iter_map* iter, t_map* map);
void iter_map_next(t_iter_map* iter);
void* iter_map_get(t_iter_map* iter);
int iter_map_end(t_iter_map* iter);

#endif
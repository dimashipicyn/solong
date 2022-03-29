#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <stdint.h>

typedef struct s_game_object
{
    void (*input)();
    void (*update)();
    void (*render)();
} t_game_object;

typedef struct s_keys t_keys;

void game_object_input(void *object, t_keys keys);
void game_object_update(void *object);
void game_object_render(void *object, void *graphics, int32_t elapsed);

#endif
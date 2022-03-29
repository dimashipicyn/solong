#include "game_object.h"
#include "keys.h"

void game_object_input(void *object, t_keys keys)
{
    (*(t_game_object**)object)->input(object, keys);
}
void game_object_update(void *object)
{
    (*(t_game_object**)object)->update(object);
}
void game_object_render(void *object, void *graphics, int32_t elapsed)
{ 
    (*(t_game_object**)object)->render(object, graphics, elapsed);
}
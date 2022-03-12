#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

typedef struct s_game_object
{
    void (*input)();
    void (*update)();
    void (*render)();
} t_game_object;

#endif
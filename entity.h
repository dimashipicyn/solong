#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

typedef struct s_game_ctx t_game_ctx;
typedef struct s_entity t_entity;

typedef struct s_entity_methods
{
    void (*input)(t_entity* entity, t_game_ctx* game_ctx);
    void (*update)(t_entity* entity, t_game_ctx* game_ctx);
    void (*render)(t_entity* entity, t_game_ctx* game_ctx);
    void (*damage)(t_entity* entity, t_game_ctx* game_ctx, int32_t damage);
    void (*free)(t_entity* entity);
} t_entity_methods;

typedef struct s_entity
{
    t_entity_methods* methods;
} t_entity;

void entity_input(t_entity* entity, t_game_ctx* game_ctx);
void entity_update(t_entity* entity, t_game_ctx* game_ctx);
void entity_render(t_entity* entity, t_game_ctx* game_ctx);
void entity_damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage);
void entity_free(t_entity* entity);

#endif

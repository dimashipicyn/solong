#include "entity.h"
#include "utils.h"
#include <assert.h>

void entity_input(t_entity* entity, t_game_ctx* game_ctx)
{
    assert(entity->methods->input);
    entity->methods->input(entity, game_ctx);
}

void entity_update(t_entity* entity, t_game_ctx* game_ctx)
{
    assert(entity->methods->update);
    entity->methods->update(entity, game_ctx);
}

void entity_render(t_entity* entity, t_game_ctx* game_ctx)
{
    assert(entity->methods->render);
    entity->methods->render(entity, game_ctx);
}

void entity_damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage)
{
    assert(entity->methods->damage);
    entity->methods->damage(entity, game_ctx, damage);
}

int entity_is_alive(t_entity* entity)
{
    assert(entity->methods->is_alive);
    return entity->methods->is_alive(entity);
}

void entity_free(t_entity* entity)
{
    assert(entity->methods->free);
    entity->methods->free(entity);
}

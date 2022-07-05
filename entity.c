#include "entity.h"

void entity_input(t_entity* entity, t_game_ctx* game_ctx)
{
    entity->methods->input(entity, game_ctx);
}

void entity_update(t_entity* entity, t_game_ctx* game_ctx)
{
    entity->methods->update(entity, game_ctx);
}

void entity_render(t_entity* entity, t_game_ctx* game_ctx)
{ 
    entity->methods->render(entity, game_ctx);
}

void entity_damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage)
{
    entity->methods->damage(entity, game_ctx, damage);
}

void entity_free(t_entity* entity)
{
    entity->methods->free(entity);
}

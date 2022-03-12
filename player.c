#include "player.h"
#include "keys.h"
#include "graphics.h"
#include "libft.h"

void input_player(t_player* player, t_keys keys)
{
    if (keys.forward) {
        player->position.x += 0.1;
    }
    if (keys.backward) {
        player->position.x -= 0.1;
    }
    if (keys.left) {
        // do_someting
    }
    if (keys.right) {
        // do_someting
    }
}

void update_player(t_player* player)
{
    // do_something
}

void render_player(t_player* player, t_graphics* graphics)
{
    // do_something
    t_rect rect = {player->position.x * 32, player->position.y * 32, 64, 64};
    t_sprite sprite = {get_texture(player->id), rect};
    draw_sprite_to_frame(graphics, sprite);
}

void init_player(t_player* player, t_point pos, t_point dir)
{
    player->interface.input = input_player;
    player->interface.update = update_player;
    player->interface.render = render_player;

    player->id = KNIGHT;
    player->position = pos;
    player->direction = dir;
}

t_player* new_player(t_point pos, t_point dir)
{
    t_player* player = ft_calloc(1, sizeof(t_player));
    init_player(player, pos, dir);
    return player;
}

void delete_player(t_player* player)
{
    free(player);
}
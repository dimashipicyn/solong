#include "game.h"
#include "graphics.h"
#include "vector.h"
#include "texture.h"
#include "libft.h"

#include <stdint.h>

void draw_number(t_graphics* graphics, t_point dest, int32_t number)
{
    t_texture *texture = get_texture(DIGITS);
    int32_t w = texture->width / 10;
    int32_t h = texture->height;
    t_rect dst = {dest.x,dest.y,16,20};
    t_rect src = {0,0,w,h};
    t_sprite sprite = {
        .dest = dst,
        .src = src,
        .texture = texture
    };

    char* snum = ft_itoa(number);

    int32_t i = 0;
    while (snum[i]) {
        int32_t idx = snum[i] - '0';
        sprite.src.x = idx * w;
        draw_sprite_to_frame(graphics, sprite);
        sprite.dest.x += (sprite.dest.width + 1);
        ++i;
    }
    free(snum);
}

static int32_t counter = 0;
static int32_t framerate = 0;
static int32_t elapsed = 0;
void draw_framerate(t_graphics* graphics, int32_t elapsed_time)
{
    ++counter;
    elapsed += elapsed_time;
    if (counter == 10) {
        framerate = 10000 / elapsed;
        elapsed = 0;
        counter = 0;
    }
    draw_number(graphics, (t_point){0,0}, framerate);
}
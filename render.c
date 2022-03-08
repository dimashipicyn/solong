#include <stdlib.h>
#include "game.h"
#include "render.h"
#include "mlx.h"

static inline int get_pixel_texture(t_texture* texture, int x, int y)
{
    register int *color = (texture->addr + (x * 4)
                                     + (y * texture->width * 4)
                                     );
    return *color;
}

static inline void set_pixel_texture(t_texture *texture, int x, int y, int color)
{
    *(int *)(texture->addr + (x * 4)
                           + (y * texture->width * 4)
                           ) = color;
}

void draw_sprite_to_frame(t_graphics* graphics, t_sprite sprite)
{
    t_texture* frame = graphics->frame;

    int x_max = sprite.rect.x + sprite.rect.width;
    int y_max = sprite.rect.y + sprite.rect.height;

    float scalex = sprite.texture->width / (float)sprite.rect.width;
    float scaley = sprite.texture->height / (float)sprite.rect.height;

    for (int y = 0; y < sprite.texture->height; ++y) {

        if (y < 0 || y > frame->height) {
            continue;
        }

        for (int x = 0; x < sprite.texture->width; ++x) {

            if (x < 0 || x > frame->width) {
                continue;
            }


            // получаем нужный пиксель с учетом масштаба
            int color = get_pixel_texture(sprite.texture, x * scalex, y * scaley);

            // черный цвет пропускаем
            if (color == 0x0) {
                continue;
            }
            
            set_pixel_texture(frame, x + sprite.rect.x, y + sprite.rect.y, color);
        }
    }
}

void clear(t_graphics* graphics)
{
    mlx_clear_window(graphics->mlx, graphics->window);
}

void render(t_graphics* graphics)
{
    mlx_put_image_to_window(graphics->mlx, graphics->window, graphics->frame->image, 0, 0);
}

t_graphics *init_graphics(int width, int height, char* title)
{
    void*       mlx;
    void*       window;
    void*       addr;
    void*       image;

    mlx = mlx_init();
    if (!mlx) {
        return NULL;
    }

    window = mlx_new_window(mlx, width, height, title);
    if (!window) {
        return NULL;
    }

    image = mlx_new_image(mlx, width, height);
    if (!image) {
        mlx_destroy_window(mlx, window);
    }

    int endian;
    int size_line;
    int bits_per_pixel;
    addr = mlx_get_data_addr(image, &bits_per_pixel, &size_line, &endian);

    t_texture *frame = calloc(1, sizeof(t_texture));
    *frame = (t_texture) {
        .image = image,
        .addr = addr,
        .bits_per_pixel = bits_per_pixel,

        .width = width,
        .height = height
    };

    t_graphics  *graphics = calloc(1, sizeof(t_graphics));

    *graphics = (t_graphics) {
        .mlx = mlx,
        .window = window,

        .frame = frame
    };

    return graphics;
}

void render_map(t_game* game)
{
    size_t row;
    size_t col;
    size_t index;
    t_map map = game->map;

    row = 0;
    while(row < map.height)
    {
        col = 0;
        while (col < map.width)
        {
            index = map.data[row][col] - '0';
            draw_sprite_to_frame(game->graphics, (t_sprite){&game->textures[index], (t_rect){col * 64, row * 64, 64, 64}});
            col++;
        }
        row++;
    }
}
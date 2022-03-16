#include <stdlib.h>
#include "game.h"
#include "graphics.h"
#include "texture.h"
#include "mlx.h"

static inline int get_pixel_texture(t_texture* texture, int x, int y)
{
    register int *color = (texture->addr + (x * texture->bits_per_pixel)
                                     + (y * texture->width * texture->bits_per_pixel)
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

    int x_max = (sprite.rect.x + sprite.rect.width) < frame->width ? sprite.rect.width : frame->width - sprite.rect.x;
    int y_max = (sprite.rect.y + sprite.rect.height) < frame->height ? sprite.rect.height : frame->height - sprite.rect.y;

    int x_min = sprite.rect.x >= 0 ? 0 : -sprite.rect.x; //sprite.rect.width + sprite.rect.x;
    int y_min = sprite.rect.y >= 0 ? 0 : -sprite.rect.y; //sprite.rect.height + sprite.rect.y;
    
    if (x_min < 0 || y_min < 0 || x_max < 0 || y_max < 0) {
        return;
    }

    float scale_x = sprite.texture->width / (float)sprite.rect.width;
    float scale_y = sprite.texture->height / (float)sprite.rect.height;

    for (int y = y_min; y < y_max; ++y) {

        for (int x = x_min; x < x_max; ++x) {

            // получаем нужный пиксель с учетом масштаба
            int color = get_pixel_texture(sprite.texture, x * scale_x, y * scale_y);

            // черный цвет пропускаем
            if (color == 0x0 || color == 0x00FFFFFF) {
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
    enum TEXTURE_ID id;
    t_game_map map = game->map;

    row = 0;
    while(row < map.height)
    {
        col = 0;
        while (col < map.width)
        {
            id = map.data[row][col] - '0';
            if (id != FLOOR_1) {
                draw_sprite_to_frame(game->graphics, (t_sprite){get_texture(FLOOR_1), (t_rect){col * 32, row * 32, 32, 32}});
            }
            draw_sprite_to_frame(game->graphics, (t_sprite){get_texture(id), (t_rect){col * 32, row * 32, 32, 32}});
            col++;
        }
        row++;
    }
}
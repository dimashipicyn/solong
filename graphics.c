#include "game.h"
#include "graphics.h"
#include "texture.h"
#include "mlx.h"

#include <stdlib.h>
#include <math.h>

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

void draw_line_to_frame(t_graphics* grapics, t_line line)
{
    int dx = fabs(line.a.x - line.b.x);
    int dy = fabs(line.a.y - line.b.y);
    int y = line.a.y;
    int e = -2 * dx;
    for(int x = line.a.x ; x <= line.b.x ; ++x) {
        set_pixel_texture(grapics->frame, x, y, 0x0089ff89);
        e += 2 * dy;
        if(e > 0) ++y;
        if(e >= dx) e -= 2 * dx;
    }    
}

void        draw_rect_to_frame(t_graphics* grapics, t_rect rect)
{

}

void        draw_circle_to_frame(t_graphics* grapics, t_circle circle)
{

}

void        draw_triangle_to_frame(t_graphics* grapics, t_triangle triangle)
{
    
}

void draw_sprite_to_frame(t_graphics* graphics, t_sprite sprite)
{
    t_texture* frame = graphics->frame;

    int x_max = (sprite.dest.x + sprite.dest.width) < frame->width ? sprite.dest.width : frame->width - sprite.dest.x;
    int y_max = (sprite.dest.y + sprite.dest.height) < frame->height ? sprite.dest.height : frame->height - sprite.dest.y;

    int x_min = sprite.dest.x >= 0 ? 0 : -sprite.dest.x;
    int y_min = sprite.dest.y >= 0 ? 0 : -sprite.dest.y;
    
    if (x_min < 0 || y_min < 0 || x_max < 0 || y_max < 0) {
        return;
    }

    float scale_x = sprite.src.width / (float)sprite.dest.width;
    float scale_y = sprite.src.height / (float)sprite.dest.height;

    for (int y = y_min; y < y_max; ++y) {

        for (int x = x_min; x < x_max; ++x) {

            // получаем нужный пиксель с учетом масштаба
            int color = get_pixel_texture(sprite.texture, sprite.src.x + x * scale_x, sprite.src.y + y * scale_y);

            // черный цвет пропускаем
            if (/* color == 0x00FFFFFF || */ color == 0x00000001) {
                continue;
            }
            
            set_pixel_texture(frame, x + sprite.dest.x, y + sprite.dest.y, color);
        }
    }
}

void clear(t_graphics* graphics)
{
    mlx_clear_window(graphics->mlx, graphics->window);
}

void render_frame(t_graphics* graphics)
{
    mlx_put_image_to_window(graphics->mlx, graphics->window, graphics->frame->image, 0, 0);
    mlx_do_sync(graphics->mlx);
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

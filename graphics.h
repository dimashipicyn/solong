#ifndef GRAPHICS_H
# define GRAPHICS_H

#include "vector.h"

#include <stdint.h>

typedef struct s_texture {
    void* image;
    void* addr;

    int width;
    int height;
    int bits_per_pixel;
} t_texture;

typedef struct s_graphics {
    void* mlx;
    void* window;

    t_texture *frame;
} t_graphics;

typedef struct s_line {
    t_vec2 a;
    t_vec2 b;
} t_line;

typedef struct s_rect {
    int x;
    int y;
    int width;
    int height;
} t_rect;

typedef struct s_circle {
    t_vec2 center;
    float radius;
} t_circle;

typedef struct s_triangle {
    t_vec2 a;
    t_vec2 b;
    t_vec2 c;
} t_triangle;

typedef struct s_sprite {
    t_texture*  texture;
    t_rect      dest;
    t_rect      src; 
} t_sprite;

typedef struct s_animation
{
    t_sprite sprite;
    int32_t nframes;
    int32_t duration;
    int32_t elapsed;
} t_animation;

typedef struct s_game t_game;

t_graphics*	init_graphics(int width, int height, char* title);
void		draw_sprite_to_frame(t_graphics* graphics, t_sprite sprite);
void		render_frame(t_graphics* graphics);
void        update_animation(t_animation* animation, int32_t elapsed_time);
void        draw_line_to_frame(t_graphics* grapics, t_line line);
void        draw_rect_to_frame(t_graphics* grapics, t_rect rect);
void        draw_circle_to_frame(t_graphics* grapics, t_circle circle);
void        draw_triangle_to_frame(t_graphics* grapics, t_triangle triangle);

#endif
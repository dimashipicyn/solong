#ifndef GRAPHICS_H
# define GRAPHICS_H

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

typedef struct s_rect {
    int x;
    int y;
    int width;
    int height;
} t_rect;

typedef struct s_sprite {
    t_texture* texture;
    t_rect     rect;
} t_sprite;

typedef struct s_game t_game;

t_graphics*	init_graphics(int width, int height, char* title);
void		draw_sprite_to_frame(t_graphics* graphics, t_sprite sprite);
void		render(t_graphics* graphics);
void        render_map(t_game* game);

#endif
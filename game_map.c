#include "game_map.h"
#include "libft.h"
#include "graphics.h"
#include "texture.h"
#include "physics.h"

#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

typedef enum {
    EMPTY,
    BRICK,
    CONCRETE,
    WATER,
    FOREST,
    ICE,
    TILE_TYPE_SIZE
} t_tile_type;

typedef struct s_terrain
{
    t_tile_type     type;
    t_physic_body*  body;
} t_terrain;

static t_sprite sprites[TILE_TYPE_SIZE] = {};

typedef struct s_game_map
{
	t_terrain*  tiles;
	int32_t     width;
	int32_t     height;
} t_game_map;

void set_empty_terrain(t_terrain* terrain)
{
    free_physic_body(terrain->body);
    terrain->body = NULL;
    terrain->type = EMPTY;
}

static int load_map(t_game_map* map, char* filename);

t_game_map* new_game_map(char* filename)
{
    t_game_map* map = ft_calloc(1, sizeof(t_game_map));

    if (load_map(map, filename)) {
        free(map);
        return NULL;
    }
    sprites[EMPTY] = (t_sprite){get_texture(DIRT_TXR_ID), {0,0,16,16}, {0,0,16,16}};
    sprites[BRICK] = (t_sprite){get_texture(TERRAIN_TXR_ID), {0,0,16,16}, {0,0,8,8}};
    sprites[CONCRETE] = (t_sprite){get_texture(TERRAIN_TXR_ID), {0,0,16,16}, {8,0,8,8}};
    sprites[FOREST] = (t_sprite){get_texture(TERRAIN_TXR_ID), {0,0,16,16}, {16,0,8,8}};
    sprites[ICE] = (t_sprite){get_texture(TERRAIN_TXR_ID), {0,0,16,16}, {24,0,8,8}};
    sprites[WATER] = (t_sprite){get_texture(TERRAIN_TXR_ID), {0,0,16,16}, {32,0,8,8}};
    return map;
}

void delete_game_map(t_game_map* game_map)
{
    free(game_map->tiles);
    free(game_map);
}

static int load_map(t_game_map* map, char* filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Dont open map!\n");
		return 1;
	}

	t_list *list = NULL;
	char *line = NULL;
	
	int res = get_next_line(fd, &line);
	while (res > 0)
	{
		ft_list_push_back(&list, line);
		res = get_next_line(fd, &line);
	}
	ft_list_push_back(&list, line);

    if (res == -1) {
        ft_list_foreach(list, free);
        ft_list_clear(&list);
        return 1;
    }

	size_t height = ft_list_size(list);
	size_t width = ft_strlen(list->content);
	t_terrain* tiles = calloc(height * width, sizeof(t_terrain));

    size_t x = 0;
    size_t y = 0;

	t_list* it_list = list;
	t_terrain* it_tiles = tiles;
	while (it_list)
	{
        char* row = it_list->content;
        x = 0;
		while (*row) {
            t_tile_type type = *row - '0';
            
            *it_tiles = (t_terrain){
                .type = type,
                .body = NULL
            };
            if (type == BRICK) {
                t_physic_body_def def = {
                    .pos = vec2(x * 16, y * 16),
                    .size = vec2(16,16),
                    .user_data = it_tiles
                };
                it_tiles->body = create_physic_body(def);
            }
            
            ++row;
            ++it_tiles;
            x++;
        }
		it_list = it_list->next;
        y++;
	}

	ft_list_clear(&list);

	map->tiles = tiles;
    map->width = width;
    map->height = height;
    return 0;
}

void draw_game_map(t_game_map* game_map, t_graphics* graphics)
{
    size_t row;
    size_t col;
    t_terrain* tiles;

    row = 0;
    tiles = game_map->tiles;
    while(row < game_map->height)
    {
        col = 0;
        while (col < game_map->width)
        {
            t_terrain terrain = tiles[row * game_map->width + col];
            t_sprite sprite = sprites[terrain.type];
            sprite.dest.x = col * sprite.dest.width;
            sprite.dest.y = row * sprite.dest.height;
            draw_sprite_to_frame(graphics, sprite);
            col++;
        }
        row++;
    }
}

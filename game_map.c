#include "game_map.h"
#include "libft.h"
#include "graphics.h"
#include "texture.h"
#include "physics.h"

#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

typedef enum {
    EMPTY       = '0' - '0',
    BRICK       = '1' - '0',
    CONCRETE    = '2' - '0',
    WATER       = '3' - '0',
    FOREST      = '4' - '0',
    ICE         = '5' - '0',
    PLAYER_1    = 'P' - '0',
    BASE_OREL   = 'B' - '0',
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
    t_vec2      start_player_pos;
} t_game_map;

void destroy_terrain(t_terrain* terrain)
{
    if (terrain->type == BRICK) {
        free_physic_body(terrain->body);
        terrain->body = NULL;
        terrain->type = EMPTY;
    }
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
    sprites[BASE_OREL] = (t_sprite){get_texture(OREL_TXR_ID), {0,0,32,32}, {0,0,16,16}};
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
            
            if (type == BRICK || type == WATER || type == CONCRETE)
            {
                t_physic_body_def def = {
                    .pos = vec2(x * 16, y * 16),
                    .size = vec2(16,16),
                    .user_data = it_tiles
                };
                it_tiles->body = create_physic_body(def);
            }
            
            if (type == PLAYER_1)
            {
                map->start_player_pos = vec2(x * 16, y * 16);
                it_tiles->type = EMPTY;
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

void draw_game_map(t_game_map* game_map, t_graphics* graphics, t_vec2 pos)
{
    size_t row;
    size_t col;
    t_terrain* tiles;
    
    t_sprite orel = {};

    row = 0;
    tiles = game_map->tiles;
    while(row < game_map->height)
    {
        col = 0;
        while (col < game_map->width)
        {
            t_terrain terrain = tiles[row * game_map->width + col];
            
            t_sprite sprite_empty = sprites[EMPTY];
            sprite_empty.dest.x = col * sprite_empty.dest.width;
            sprite_empty.dest.y = row * sprite_empty.dest.height;
            draw_sprite_to_frame(graphics, sprite_empty);
            
            t_sprite sprite = sprites[terrain.type];
            sprite.dest.x = col * 16;
            sprite.dest.y = row * 16;
            
            if (terrain.type == BASE_OREL) {
                orel = sprite;
            }
            
            draw_sprite_to_frame(graphics, sprite);
            col++;
        }
        row++;
    }
    draw_sprite_to_frame(graphics, orel);
}

t_vec2 get_start_player_pos(t_game_map* map)
{
    return map->start_player_pos;
}
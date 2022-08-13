#include "game_map.h"
#include "utils.h"
#include "graphics.h"
#include "texture.h"
#include "physics.h"
#include "entity.h"

#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    EMPTY       = '0' - '0',
    BRICK       = '1' - '0',
    CONCRETE    = '2' - '0',
    WATER       = '3' - '0',
    FOREST      = '4' - '0',
    ICE         = '5' - '0',
    PLAYER_1    = 'P' - '0',
	PLAYER_2    = 'T' - '0',
	ENEMY    	= 'E' - '0',
    BASE_OREL   = 'B' - '0',
    TILE_TYPE_SIZE
} t_tile_type;

enum {
    DEFAULT_ARMOR = 0,
    BRICK_ARMOR = 100,
    CONCRETE_ARMOR = 500
};

typedef struct s_terrain
{
    t_entity_methods*  methods;
    t_tile_type     type;
    t_physic_body*  body;
    int32_t         armor;
} t_terrain;

typedef struct s_game_map
{
	t_terrain*  tiles;
	size_t		width;
	size_t		height;
    t_vec2      player_one_spawn_pos;
	t_vec2      player_two_spawn_pos;
	t_vec2      enemies_spawn_pos;
} t_game_map;

static void damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage)
{
	(void)game_ctx;

    t_terrain* terrain = (t_terrain*)entity;
    
    terrain->armor -= damage;
    if (terrain->armor <= 0) {
        free_physic_body(terrain->body);
        terrain->body = NULL;
        terrain->type = EMPTY;
    }
}

static t_entity_methods map_methods = {
    .damage = damage
};

static t_sprite sprites[TILE_TYPE_SIZE];

static int load_map(t_game_map* map, char* filename);

t_game_map* new_game_map(char* filename)
{
    t_game_map* map = calloc(1, sizeof(t_game_map));

    if (load_map(map, filename)) {
        free(map);
        return NULL;
    }

    sprites[EMPTY]		= (t_sprite){get_texture(DIRT_TXR_ID),    {vec2(0,0),vec2(16,16)}, {vec2(0,0),vec2(16,16)}};
    sprites[BRICK]		= (t_sprite){get_texture(TERRAIN_TXR_ID), {vec2(0,0),vec2(16,16)}, {vec2(0,0),vec2(8,8)}};
    sprites[CONCRETE]	= (t_sprite){get_texture(TERRAIN_TXR_ID), {vec2(0,0),vec2(16,16)}, {vec2(8,0),vec2(8,8)}};
    sprites[FOREST]		= (t_sprite){get_texture(TERRAIN_TXR_ID), {vec2(0,0),vec2(16,16)}, {vec2(16,0),vec2(8,8)}};
    sprites[ICE]		= (t_sprite){get_texture(TERRAIN_TXR_ID), {vec2(0,0),vec2(16,16)}, {vec2(24,0),vec2(8,8)}};
    sprites[WATER]		= (t_sprite){get_texture(TERRAIN_TXR_ID), {vec2(0,0),vec2(16,16)}, {vec2(32,0),vec2(8,8)}};
    sprites[BASE_OREL]	= (t_sprite){get_texture(OREL_TXR_ID),    {vec2(0,0),vec2(32,32)}, {vec2(0,0),vec2(16,16)}};
    
    return map;
}

void delete_game_map(t_game_map* game_map)
{
    free(game_map->tiles);
    free(game_map);
}

int32_t get_physics_layer_from_type(t_tile_type type)
{
    switch (type)
    {
    case BRICK:
    case CONCRETE:
        return PHYSICS_LAYER_1;
    case WATER:
        return PHYSICS_LAYER_2;
    
    default:
        break;
    }
    return PHYSICS_LAYER_EMPTY;
}

int32_t get_armor_from_type(t_tile_type type)
{
    switch (type)
    {
    case BRICK:
        return BRICK_ARMOR;
    case CONCRETE:
        return CONCRETE_ARMOR;
    default:
        break;
    }
    return DEFAULT_ARMOR;
}

void init_terrain(t_terrain* terrain, t_tile_type type, int x, int y)
{
    terrain->type = type;
    terrain->body = NULL;
    terrain->methods = &map_methods;
    terrain->armor = get_armor_from_type(type);

    if (type == BRICK || type == WATER || type == CONCRETE)
    {
        t_physic_body_def def = {
            .pos = vec2(x * 16 + 8, y * 16 + 8),
            .size = vec2(8, 8),
            .user_data = terrain,
            .layer = get_physics_layer_from_type(type)
        };

        terrain->body = create_physic_body(def);
    }
}

static int load_map(t_game_map* map, char* filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Dont open map!\n");
		return 1;
	}

	t_list *list = NULL;
	char *line = NULL;
	
	int res = get_next_line(fd, &line);
	while (res > 0)
	{
		ut_list_push_back(&list, line);
		res = get_next_line(fd, &line);
	}
	ut_list_push_back(&list, line);

    if (res == -1) {
        ut_list_foreach(list, free);
        ut_list_clear(&list);
        return 1;
    }

	size_t height = ut_list_size(list);
	size_t width = strlen(list->content);
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

            init_terrain(it_tiles, type, x, y);

            if (type == PLAYER_1)
            {
                map->player_one_spawn_pos = vec2(x * 16, y * 16);
                it_tiles->type = EMPTY;
            }
			if (type == PLAYER_2)
            {
                map->player_two_spawn_pos = vec2(x * 16, y * 16);
                it_tiles->type = EMPTY;
            }
			if (type == ENEMY)
            {
                map->enemies_spawn_pos = vec2(x * 16, y * 16);
                it_tiles->type = EMPTY;
            }

            ++row;
            ++it_tiles;
            x++;
        }
		it_list = it_list->next;
        y++;
	}

	ut_list_clear(&list);

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
    
    t_sprite orel = {0};

    row = 0;
    tiles = game_map->tiles;
    while(row < game_map->height)
    {
        col = 0;
        while (col < game_map->width)
        {
            t_terrain terrain = tiles[row * game_map->width + col];
            
            t_sprite sprite_empty = sprites[EMPTY];
            sprite_empty.dest.pos.x = col * sprite_empty.dest.size.x;
            sprite_empty.dest.pos.y = row * sprite_empty.dest.size.y;
            draw_sprite_to_frame(graphics, sprite_empty);
            
            t_sprite sprite = sprites[terrain.type];
            sprite.dest.pos.x = col * 16;
            sprite.dest.pos.y = row * 16;
            
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

t_vec2 get_player_one_spawn_pos(t_game_map* map)
{
    return map->player_one_spawn_pos;
}

t_vec2 get_player_two_spawn_pos(t_game_map* map)
{
	return map->player_two_spawn_pos;
}

t_vec2 get_enemies_spawn_pos(t_game_map* map)
{
	return map->enemies_spawn_pos;
}

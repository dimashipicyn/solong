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
	t_physic_body* bodyes[4];
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

t_game_map* new_game_map()
{
    t_game_map* map = calloc(1, sizeof(t_game_map));

	size_t height = 28;
	size_t width = 28;
	t_terrain* tiles = calloc(height * width, sizeof(t_terrain));

	map->width = width;
    map->height = height;
	map->tiles = tiles;

	for (size_t y = 0; y < map->height; y++) {
		for (size_t x = 0; x < map->width; x++) {
			t_tile_type type = EMPTY;

			init_terrain(map, type, x, y);
		}
	}

	map->player_one_spawn_pos = vec2(11 * 16, 25 * 16);
	map->player_two_spawn_pos = vec2(19 * 16, 26 * 16);
	map->enemies_spawn_pos = vec2(2 * 16, 2 * 16);

	t_physic_body_def def = {
		.pos = vec2(-5, -5),
		.size = vec2(28 * 16, 5),
		.user_data = NULL,
		.layer = PHYSICS_LAYER_1
	};
	map->bodyes[0] = create_physic_body(def);

	def.size = vec2(5, 28 * 16);
	map->bodyes[1] = create_physic_body(def);

	def.pos = vec2(28 * 16 + 5, -5);
	map->bodyes[2] = create_physic_body(def);

	def.pos = vec2(-5, 28 * 16 + 5);
	def.size = vec2(28 * 16, 5);
	map->bodyes[3] = create_physic_body(def);

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
	for (size_t i = 0; i < 28 * 28; i++) {
		t_terrain* t = &game_map->tiles[i];
		if (t->body) {
			free_physic_body(t->body);
		}
	}

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

void init_terrain(t_game_map* map, t_tile_type type, int x, int y)
{
	t_terrain* terrain = &map->tiles[y * map->width + x];

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

void destroy_terrain(t_game_map* map, int x, int y)
{
	t_terrain* terrain = &map->tiles[y * map->width + x];

	if (terrain->body) {
		free_physic_body(terrain->body);
	}
	terrain->type = EMPTY;
}

int load_map(t_game_map* map, char* filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Dont open map!\n");
		return 1;
	}

	char buf[29] = {0};

	for (size_t y = 0; y < map->height; y++) {
		read(fd, buf, 29);
		for (size_t x = 0; x < map->width; x++) {
			t_tile_type type = buf[x] - '0';

			init_terrain(map, type, x, y);
		}
	}

    return 0;
}

int save_map(t_game_map* map, char* filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		printf("Dont open map!\n");
		return 1;
	}

	size_t height = 28;
	size_t width = 28;

	char buf[29];
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			t_tile_type type = map->tiles[y * width + x].type;

			buf[x] = type + '0';
		}
		buf[28] = '\n';
		write(fd, buf, 29);
	}

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
	if (orel.texture) {
		draw_sprite_to_frame(graphics, orel);
	}
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

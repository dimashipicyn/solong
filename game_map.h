#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "vector.h"
#include "entity.h"
#include "physics.h"
#include "graphics.h"

#include <stddef.h>
#include <stdint.h>

typedef struct s_graphics t_graphics;
typedef struct s_game_map t_game_map;

typedef enum {
    EMPTY,
    BRICK ,
    CONCRETE,
    WATER,
    FOREST,
    ICE,
    BASE_OREL,
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
	t_sprite	sprites[TILE_TYPE_SIZE];
	t_physic_body* bodyes[4];
} t_game_map;

t_game_map* new_game_map();
void delete_game_map(t_game_map* game_map);
void init_terrain(t_game_map* map, t_tile_type type, int x, int y);
void draw_game_map(t_game_map* game_map, t_graphics* graphics);
//t_vec2 get_player_one_spawn_pos(t_game_map* map);
//t_vec2 get_player_two_spawn_pos(t_game_map* map);
//t_vec2 get_enemies_spawn_pos(t_game_map* map);
int load_map(t_game_map* map, char* filename);
int save_map(t_game_map* map, char* filename);

#endif

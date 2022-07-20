#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

#include "entity.h"
#include "vector.h"
#include "texture.h"
#include "graphics.h"
#include "physics.h"
#include "animation.h"
#include "command.h"

enum
{
	TANK_SPAWN_ANIMATION,
    TANK_ANIMATION,
    TANK_ARMOR_ANIMATION,
    TANK_TOTAL_ANIMATIONS
};

typedef enum e_tank_input_type
{
	PLAYER_ONE_INPUT_TYPE,
	PLAYER_TWO_INPUT_TYPE,
	ENEMY_INPUT_TYPE
} t_tank_input_type;

typedef t_command (*handleInput)(t_entity* entity, t_game_ctx* game_ctx);

typedef struct s_tank
{
    t_entity_methods*	methods;
    t_physic_body*		body;
    handleInput     	input;
    t_animation     	anim[TANK_TOTAL_ANIMATIONS];
    int64_t         	last_fire_time;
    int64_t         	birth_date;
	float				velocity;
	float				bullet_velocity;
	int32_t				recharge_time;
    int8_t         		active_animations;
    int8_t          	hitpoints;
	int8_t				damage;
	int8_t				bullet_damage;
    int8_t          	armor;
    int8_t          	is_alive;
	int8_t				state;
} t_tank;

typedef struct s_tank_def
{
	t_vec2				pos;
	t_vec2				dir;
	t_tank_input_type	input_type;
	float				velocity;
	float				bullet_velocity;
	int32_t				recharge_time;
	int8_t				hitpoints;
	int8_t				damage;
	int8_t				bullet_damage;
	
} t_tank_def;

t_tank* new_tank(t_tank_def def);
void delete_tank(t_tank* tank);

#endif

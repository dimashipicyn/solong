#ifndef GAME_H
# define GAME_H

#include "graphics.h"
#include "keys.h"
#include "scene.h"

#include <stdint.h>

typedef struct s_graphics t_graphics;
typedef struct s_keys t_keys;

typedef enum e_scene_type {
	MENU_SCENE,
    MAIN_SCENE,
	EDITOR_SCENE,
    TOTAL_SCENES
} t_scene_type;

typedef struct s_game_ctx {
    t_graphics  	*graphics;
    t_scene     	*scenes[TOTAL_SCENES];
    t_scene     	*active_scene;
    const uint8_t	*keys;
	t_mouse			mouse;
	int64_t			lag;
	int64_t			previous_time;
    int64_t     	elapsed;
} t_game_ctx;

#endif

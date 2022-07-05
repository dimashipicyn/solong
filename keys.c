#include "keys.h"
#include "game.h"

# define STEP_TURN 0.03
# define STEP_MOVE 0.1
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

int			key_init(int keycode, t_game_ctx* game_ctx)
{
	t_keys* keys = &game_ctx->keys;

	if (keycode == LEFT)
		keys->left = 1;
	if (keycode == RIGHT)
		keys->right = 1;
	if (keycode == W)
		keys->forward = 1;
	if (keycode == S)
		keys->backward = 1;
	if (keycode == A)
		keys->left_move = 1;
	if (keycode == D)
		keys->right_move = 1;

	return (0);
}

int			key_destroy(int keycode, t_game_ctx* game_ctx)
{
	t_keys* keys = &game_ctx->keys;

	if (keycode == LEFT)
		keys->left = 0;
	if (keycode == RIGHT)
		keys->right = 0;
	if (keycode == W)
		keys->forward = 0;
	if (keycode == S)
		keys->backward = 0;
	if (keycode == A)
		keys->left_move = 0;
	if (keycode == D)
		keys->right_move = 0;
	
	return (0);
}

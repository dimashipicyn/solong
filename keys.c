#include "keys.h"
#include "game.h"

int			key_init(int keycode, t_game* game)
{
	t_keys* keys = &game->keys;

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

int			key_destroy(int keycode, t_game* game)
{
	t_keys* keys = &game->keys;

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

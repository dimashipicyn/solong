#ifndef KEYS_H
# define KEYS_H

typedef struct			s_keys
{
	int					left;
	int					right;
	int					forward;
	int					backward;
	int					left_move;
	int					right_move;
}						t_keys;

typedef struct s_game_ctx t_game_ctx;

int		key_init(int keycode, t_game_ctx* game);
int		key_destroy(int keycode, t_game_ctx* game);

#endif

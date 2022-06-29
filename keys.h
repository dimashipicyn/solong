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

typedef struct s_game t_game;

int		key_init(int keycode, t_game* game);
int		key_destroy(int keycode, t_game* game);

#endif

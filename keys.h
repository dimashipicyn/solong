#ifndef KEYS_H
# define KEYS_H
# define STEP_TURN 0.03
# define STEP_MOVE 0.1
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

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

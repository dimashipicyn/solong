/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbespin <lbespin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:35:55 by lbespin           #+#    #+#             */
/*   Updated: 2021/02/18 19:00:47 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

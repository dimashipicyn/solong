//
//  animation.h
//  solong
//
//  Created by Dmitry Shipicyn on 30.06.2022.
//

#ifndef animation_h
#define animation_h

#include "graphics.h"

#include <stdint.h>

typedef struct s_animation
{
    t_sprite sprite;
    int32_t nframes;
    int32_t duration;
    int32_t elapsed;
    uint8_t index;
    char    repeat;
    char    is_end;
} t_animation;

t_animation animation(t_sprite sprite, int32_t nframes, int32_t duration, char repeat);
void        update_animation(t_animation* animation, int32_t elapsed_time);
t_sprite    get_animation_sprite(t_animation* animation);

#endif /* animation_h */

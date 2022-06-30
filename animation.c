//
//  animation.c
//  ft
//
//  Created by Dmitry Shipicyn on 30.06.2022.
//

#include "animation.h"
#include "graphics.h"

#include <math.h>

t_animation animation(t_sprite sprite, int32_t nframes, int32_t duration, char repeat)
{
    t_animation a = {sprite, nframes, duration, 0, 0, repeat, 0};
    
    return a;
}

void update_animation(t_animation* animation, int32_t elapsed_time)
{
    int32_t index = animation->nframes * animation->elapsed / animation->duration % animation->nframes;
    index = animation->repeat ? index % animation->nframes : fmin(index, animation->nframes - 1);
    
    animation->index = index;
    animation->elapsed += elapsed_time;
    
    if (animation->elapsed >= animation->duration) {
        animation->is_end = 1;
    }
    //animation->elapsed %= animation->duration;
}

t_sprite get_animation_sprite(t_animation* animation)
{
    t_sprite s = animation->sprite;
    
    s.src.x = s.src.x + (s.src.width * animation->index);
    
    return s;
}

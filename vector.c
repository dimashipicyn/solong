#include "vector.h"

#include <math.h>

double vec2_length(t_vec2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

t_vec2 vec2_add(t_vec2 v1, t_vec2 v2)
{
    return (t_vec2){v1.x + v2.x, v1.y + v2.y};
}

t_vec2 vec2_sub(t_vec2 v1, t_vec2 v2)
{
    return (t_vec2){v1.x - v2.x, v1.y - v2.y};
}

t_vec2 vec2_scalar_num(t_vec2 v, float n)
{
    return (t_vec2){v.x * n, v.y * n};
}

double vec2_distance(t_vec2 v1, t_vec2 v2)
{
    return vec2_length(vec2_sub(v1, v2));
}

t_vec2 vec2_normalize(t_vec2 v)
{
    double len = vec2_length(v);
    return (t_vec2){v.x * len, v.y * len};
}

double vec2_scalar_vec2(t_vec2 v1, t_vec2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

t_vec2 vec2_rotate(t_vec2 v, float angle)
{
    t_vec2 rv;

    rv.x = v.x * cos(angle) - v.y * sin(angle);
    rv.y = v.x * sin(angle) + v.y * cos(angle);

    return rv;
}

t_vec2 vec2(float x, float y)
{
    return (t_vec2){x, y};
}
#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_point
{
    float x;
    float y;
} t_point;

typedef struct s_vec2
{
    float x;
    float y;
} t_vec2;

double vec2_length(t_vec2 v);
t_vec2 vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2 vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2 vec2_scalar_num(t_vec2 v, float n);
double vec2_distance(t_vec2 v1, t_vec2 v2);
t_vec2 vec2_normalize(t_vec2 v);
double vec2_scalar_vec2(t_vec2 v1, t_vec2 v2);
t_vec2 vec2_rotate(t_vec2 v, float angle);
double vec2_cos();
t_vec2 vec2(float x, float y);


#endif


#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct s_settings
{
    int resolution_w;
    int resolution_h;
    char* game_name;
} t_settings;

int load_settings(char* filename);
t_settings* get_settings();

#endif
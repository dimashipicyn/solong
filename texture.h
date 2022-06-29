#ifndef TEXTURE_H
#define TEXTURE_H

typedef enum texture_id {
	TANK_YELLOW_TXR_ID,
	TANK_GREEN_TXR_ID,
	TANK_RED_TXR_ID,
	TANK_WHITE_TXR_ID,
	BULLET_TXR_ID,
	TERRAIN_TXR_ID,
	RESPAWN_TXR_ID,
	EFFECTS_TXR_ID,
	BONUSES_TXR_ID,
	OREL_TXR_ID,
	DIRT_TXR_ID,
	DIGITS_TXR_ID,
    TOTAL_TEXTURES
} t_texture_id;

typedef struct s_texture {
    void* image;
    void* addr;

    int width;
    int height;
    int bits_per_pixel;
	int endian;
	int line_len;
} t_texture;

typedef struct s_graphics t_graphics;

int load_textures(t_graphics* ctx);
t_texture* get_texture(t_texture_id id);
void set_texture_filename(char* filename, t_texture_id id);

#endif
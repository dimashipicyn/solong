#include "libft.h"
#include "mlx.h"

#include "texture.h"
#include "graphics.h"
#include "game.h"

#include <stddef.h>
#include <assert.h>

#include <SDL.h>
#include <SDL_image.h>

static t_texture textures[TOTAL_TEXTURES];

t_texture* get_texture(t_texture_id id)
{
	assert(id >= 0 && id < TOTAL_TEXTURES);
    return &textures[id];
}

static char *texture_filenames[TOTAL_TEXTURES] = {
	[TANK_YELLOW_TXR_ID] = "/assets/tank_yellow_spritesheet.png",
	[TANK_GREEN_TXR_ID]  = "/assets/tank_green_spritesheet.png",
	[TANK_RED_TXR_ID]    = "/assets/tank_red_spritesheet.png",
	[TANK_WHITE_TXR_ID]  = "/assets/tank_white_spritesheet.png",
	[BULLET_TXR_ID]      = "/assets/bullet_spritesheet.png",
	[TERRAIN_TXR_ID]     = "/assets/terrain_spritesheet.png",
	[RESPAWN_TXR_ID]     = "/assets/respawn_spritesheet.png",
	[EFFECTS_TXR_ID]     = "/assets/effects_spritesheet.png",
	[BONUSES_TXR_ID]     = "/assets/bonuses_spritesheet.png",
	[OREL_TXR_ID]        = "/assets/orel_spritesheet.png",
	[DIRT_TXR_ID]        = "/assets/dirt.png",
	[DIGITS_TXR_ID]      = "/assets/digits_spritesheet.png"
};

void set_texture_filename(char* filename, t_texture_id id)
{
	assert(id >= 0 && id < TOTAL_TEXTURES);
	texture_filenames[id] = filename;
}

enum { MAX_SIZE_PATH = 256 };

int load_textures(t_graphics* ctx, char* path_to_cur_dir)
{
	IMG_Init(IMG_INIT_PNG);
	char filename[MAX_SIZE_PATH];
	int txr_id = 0;
	while (txr_id < TOTAL_TEXTURES)
	{
		ft_memset(filename, 0, MAX_SIZE_PATH);
		ft_strlcat(filename, path_to_cur_dir, MAX_SIZE_PATH);
		ft_strlcat(filename, texture_filenames[txr_id], MAX_SIZE_PATH);
		
		t_texture texture = {NULL, NULL, 0, 0, 0, 0, 0};
		
		//if (ft_strcmp(".xpm", ft_strrchr(filename, '.')) == 0) {
		//	texture.image = mlx_xpm_file_to_image(ctx->mlx, filename, &texture.width, &texture.height);
		//}

		SDL_Surface* image = IMG_Load(filename);
		texture.texture = SDL_CreateTextureFromSurface(ctx->renderer, image);
		
		if (texture.texture == NULL) {
			ft_printf("Could not load texture: %s\n", filename);
			goto error;
		}
		
		textures[txr_id] = texture;
		txr_id++;
	}

	return 0;

error:
	for (int i = 0; i < TOTAL_TEXTURES; i++) {
		if (textures[i].texture) {
			SDL_DestroyTexture(textures[i].texture);
		}
	}
	return 1;
}

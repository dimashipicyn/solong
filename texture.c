#include "libft.h"
#include "mlx.h"

#include "texture.h"
#include "graphics.h"
#include "game.h"

#include <stddef.h>
#include <assert.h>

static t_texture textures[TOTAL_TEXTURES];

t_texture* get_texture(t_texture_id id)
{
	assert(id >= 0 && id < TOTAL_TEXTURES);
    return &textures[id];
}

static char *texture_filenames[TOTAL_TEXTURES] = {
	[TANK_YELLOW_TXR_ID] = "/assets/tank_yellow_spritesheet.xpm",
	[TANK_GREEN_TXR_ID]  = "/assets/tank_green_spritesheet.xpm",
	[TANK_RED_TXR_ID]    = "/assets/tank_red_spritesheet.xpm",
	[TANK_WHITE_TXR_ID]  = "/assets/tank_white_spritesheet.xpm",
	[BULLET_TXR_ID]      = "/assets/bullet_spritesheet.xpm",
	[TERRAIN_TXR_ID]     = "/assets/terrain_spritesheet.xpm",
	[RESPAWN_TXR_ID]     = "/assets/respawn_spritesheet.xpm",
	[EFFECTS_TXR_ID]     = "/assets/effects_spritesheet.xpm",
	[BONUSES_TXR_ID]     = "/assets/bonuses_spritesheet.xpm",
	[OREL_TXR_ID]        = "/assets/orel_spritesheet.xpm",
	[DIRT_TXR_ID]        = "/assets/dirt.xpm",
	[DIGITS_TXR_ID]      = "/assets/digits_spritesheet.xpm"
};

void set_texture_filename(char* filename, t_texture_id id)
{
	assert(id >= 0 && id < TOTAL_TEXTURES);
	texture_filenames[id] = filename;
}

enum { MAX_SIZE_PATH = 256 };

int load_textures(t_graphics* ctx, char* path_to_cur_dir)
{
	char filename[MAX_SIZE_PATH];
	int txr_id = 0;
	while (txr_id < TOTAL_TEXTURES)
	{
		ft_memset(filename, 0, MAX_SIZE_PATH);
		ft_strlcat(filename, path_to_cur_dir, MAX_SIZE_PATH);
		ft_strlcat(filename, texture_filenames[txr_id], MAX_SIZE_PATH);
		
		t_texture texture = {NULL, NULL, 0, 0, 0, 0, 0};
		
		if (ft_strcmp(".xpm", ft_strrchr(filename, '.')) == 0) {
			texture.image = mlx_xpm_file_to_image(ctx->mlx, filename, &texture.width, &texture.height);
		}
		
		if (texture.image == NULL) {
			ft_printf("Could not load texture: %s\n", filename);
			goto error;
		}

		texture.addr = mlx_get_data_addr(texture.image, &texture.bits_per_pixel, &texture.line_len, &texture.endian);
        texture.bits_per_pixel /= 8; // bytes
		
		textures[txr_id] = texture;
		txr_id++;
	}

	return 0;

error:
	for (int i = 0; i < TOTAL_TEXTURES; i++) {
		if (textures[i].image) {
			mlx_destroy_image(ctx->mlx, textures[i].image);
		}
	}
	return 1;
}

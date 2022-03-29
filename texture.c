#include <stddef.h>
#include "libft.h"
#include "mlx.h"

#include "texture.h"
#include "graphics.h"
#include "game.h"

static t_texture textures[TOTAL_TEXTURES] = {};

t_texture* get_texture(enum TEXTURE_ID id)
{
    return &textures[id];
}

char *texture_paths[] = {
	// floors
	"assets/tiles/floor/floor_5.xpm",

	// walls
	"assets/tiles/wall/wall_1.xpm",
	"assets/tiles/wall/wall_top_1.xpm",
	"assets/tiles/wall/wall_top_right.xpm",
	"assets/tiles/wall/wall_top_left.xpm",
	"assets/tiles/wall/wall_top_inner_right_2.xpm",
	"assets/tiles/wall/wall_top_inner_left_2.xpm",

	// heroes
	"assets/heroes/knight/knight_run_spritesheet.xpm",
	"assets/heroes/knight/knight_idle_spritesheet.xpm",
	"assets/digits.xpm"
};

const int MAX_SIZE_PATH = 256;


void load_textures(t_game* game)
{
	char buffer[MAX_SIZE_PATH] = {0};
	int i = -1;
	while (++i < TOTAL_TEXTURES)
	{
		ft_memset(buffer, 0, MAX_SIZE_PATH);
		ft_strlcat(buffer, "/Users/dmiitry/program/solong/", MAX_SIZE_PATH);
		ft_strlcat(buffer, texture_paths[i], MAX_SIZE_PATH);
		
		char *filename = buffer;

		t_texture texture = {};
		
		if (ft_strcmp(".xpm", ft_strrchr(filename, '.')) == 0) {
			texture.image = mlx_xpm_file_to_image(game->graphics->mlx, filename, &texture.width, &texture.height);
		}
		else if (ft_strcmp(".png", ft_strrchr(filename, '.')) == 0) {
			//texture.image = mlx_png_file_to_image(game->graphics->mlx, filename, &texture.width, &texture.height);
		}
		if (texture.image == NULL) {
			ft_printf("Could not load texture: %s\n", filename);
			continue;
		}

		int line_length = 0;
		int endian = 0;

		texture.addr = mlx_get_data_addr(texture.image, &texture.bits_per_pixel, &line_length, &endian);
        texture.bits_per_pixel /= 8;
		textures[i] = texture;
	}
}
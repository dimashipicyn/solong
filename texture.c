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
	// walls
	//"assets/tiles/wall/wall_1.png",
	//"assets/tiles/wall/wall_2.png",
	//"assets/tiles/wall/wall_3.png",
	//"assets/tiles/wall/wall_crack.png",
	// heroes
	//"assets/heroes/knight/knight_idle_anim_f0.png"
    "assets/wall_1.xpm",
    "assets/wall_2.xpm",
    "assets/wall_3.xpm",
    "assets/wall_4.xpm",
    "assets/sprite_1.xpm"
};

void load_textures(t_game* game)
{
	int i = -1;
	while (++i < TOTAL_TEXTURES)
	{
		char *filename = texture_paths[i];

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

		textures[i] = texture;
	}
}
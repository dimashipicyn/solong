#include "game_map.h"
#include "libft.h"
#include "graphics.h"
#include "texture.h"

#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_terrain
{
    t_texture* texture;
    int32_t movementCost;
    int8_t isWater;
} t_terrain;

t_terrain wall;
t_terrain flor;

typedef struct s_game_map
{
	t_terrain** tiles;
	uint32_t width;
	uint32_t height;
} t_game_map;

static int load_map(t_game_map* map, char* filename);

t_game_map* new_game_map(char* filename)
{
    t_game_map* map = ft_calloc(1, sizeof(t_game_map));

    if (load_map(map, filename)) {
        free(map);
        return NULL;
    }
    wall.texture = get_texture(WALL_1);
    flor.texture = get_texture(FLOOR_1);
    return map;
}

void delete_game_map(t_game_map* game_map)
{
    t_terrain** tiles = game_map->tiles;
    while (*tiles) {
        free(*tiles);
        ++tiles;
    }
    free(game_map->tiles);
    free(game_map);
}

static int load_map(t_game_map* map, char* filename)
{
	int fd;

	fd = open("../map.ber", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Dont open map!\n");
		return 1;
	}

	t_list *list = NULL;
	char *line = NULL;
	
	int res = get_next_line(fd, &line);
	while (res > 0)
	{
		ft_list_push_back(&list, line);
		res = get_next_line(fd, &line);
	}
	ft_list_push_back(&list, line);

    if (res == -1) {
        ft_list_foreach(list, free);
        ft_list_clear(&list);
        return 1;
    }

	size_t height = ft_list_size(list);
	size_t width = ft_strlen(list->content);
	t_terrain** tiles = calloc(height * width + 1, sizeof(void*));

	t_list* it_list = list;
	t_terrain** it_tiles = tiles;
	while (it_list)
	{
        char* row = it_list->content;
		while (*row) {
            uint8_t index = *row - '0';
            if (index == 0)
                *it_tiles = &wall;
            if (index == 1)
                *it_tiles = &flor;
            
            ++row;
            ++it_tiles;
        }
		it_list = it_list->next;
	}
	*it_tiles = NULL;

	ft_list_clear(&list);

	map->tiles = tiles;
    map->width = width;
    map->height = height;
    return 0;
}

void draw_game_map(t_game_map* game_map, t_graphics* graphics)
{
    size_t row;
    size_t col;
    t_terrain** tiles;

    row = 0;
    tiles = game_map->tiles;
    while(row < game_map->height)
    {
        col = 0;
        while (col < game_map->width)
        {
            t_terrain* terrain = tiles[row * game_map->width + col];
            draw_sprite_to_frame(graphics, (t_sprite){terrain->texture, {col * 32, row * 32, 32, 32}, {0,0,16,16}});
            col++;
        }
        row++;
    }
}
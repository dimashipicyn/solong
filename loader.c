#include <fcntl.h>


#include "game.h"
#include "mlx.h"
#include "libft.h"
#include "utils.h"

void load_map(t_game *game)
{
	int fd;

	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Dont open map!\n");
		return;
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


	size_t height = ft_list_size(list);
	size_t width = ft_strlen(list->content);
	char **map = calloc(height + 1, sizeof(char*));

	ft_printf("map w %d, h %d\n", width, height);

	t_list *it_list = list;
	char **it_map = map;
	while (it_list)
	{
		*it_map = it_list->content;

		it_map++;
		it_list = it_list->next;
	}
	*it_map = NULL;

	ft_list_clear(&list);

	game->map = (t_game_map){map, width, height};
}

typedef struct s_pair {
	char* key;
	char* value;
} t_pair;

t_pair* new_pair(char* key, char* value)
{
	t_pair* pair = ft_calloc(1, sizeof(t_pair));

	pair->key = key;
	pair->value = value;
	return pair;
}

void free_pair(t_pair* pair)
{
	free(pair->key);
	free(pair->value);
	free(pair);
}

int cmp_pair(char* key, t_pair* pair)
{
	return ft_strcmp(key, pair->key);
}

void parse_config(t_game* game, t_list* config_file_data)
{
	t_map* settings = new_map(new_pair, free_pair, cmp_pair);
	while (config_file_data)
	{
		char* line = config_file_data->content;
		char* found_delim = ft_strchr(line, ':');
		if (found_delim == NULL) {
			ft_printf("Config parser error! ':' not found.\n");
			exit(1);
		}
		char* key = ft_substr(line, 0, found_delim - line);
		char* value = ft_strdup(found_delim + 1);
		map_insert(settings, key, value);
		free(line);
		config_file_data = config_file_data->next;
	}
	t_iter_map iter;
	for (init_iter_map(&iter, settings); !iter_map_end(&iter); iter_map_next(&iter))
	{
		t_pair* pair = iter_map_get(&iter);
		ft_printf("Key: %s, value: %s\n", pair->key, pair->value);
	}
	game->settings = settings;
}

void load_config(t_game *game)
{
	int fd = open("config.yml", O_RDONLY);
	if (fd == -1) {
		ft_printf("Dont open config!\n");
		exit(1);
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
	parse_config(game, list);
	ft_list_clear(&list);
}
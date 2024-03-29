#include <fcntl.h>

#include "settings.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static t_settings settings;

t_settings* get_settings()
{
	return &settings;
}

static char* setting_name[] = {
	"resolution_w",
	"resolution_h",
	"game_name",
	NULL
};

static int parse_line(char* line)
{
	char* found_delim = strchr(line, ':');
	if (found_delim == NULL) {
		printf("Parse settings error! ':' not found. Line: %s\n", line);
		goto error;
	}
	*found_delim = '\0';

	char* name = line;
	char* value = found_delim + 1;
	if (!strcmp(setting_name[0], name)) {
		settings.resolution_w = atoi(value);
	}
	else if (!strcmp(setting_name[1], name)) {
		settings.resolution_h = atoi(value);
	}
	else if (!strcmp(setting_name[2], name)) {
		settings.game_name = strdup(value);
	}
	else {
		printf("Unrecognized option: %s\n", name);
		goto error;
	}

	return 0;

error:
	return 1;
}

int load_settings(char* filename)
{
	char *line = NULL;

	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		printf("Dont open settings: %s!\n", filename);
		goto error;
	}
	
	int res = get_next_line(fd, &line);
	while (res > 0)
	{
		if (parse_line(line)) {
			goto error;
		}
		free(line);
		line = NULL;

		res = get_next_line(fd, &line);
	}

	if (res == -1 || parse_line(line)) {
		goto error;
	}

	free(line);
	line = NULL;

	return 0;

error:
	free(line);
	close(fd);
	return 1;
}

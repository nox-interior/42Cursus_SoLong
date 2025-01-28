void	ft_init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
}

void	ft_init_config(t_config *config)
{
	int32_t	monitor_width;
	int32_t	monitor_height;

	monitor_width = 0;
	monitor_height = 0;
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	if (monitor_width <= 0 || monitor_height <= 0)
	{
		monitor_width = 1920;
		monitor_height = 1080;
	}
	config->screen_width = monitor_width;
	config->screen_height = monitor_height;
	config->max_map_width = (uint32_t)(monitor_width / TILE_SIZE);
	config->max_map_height = (uint32_t)(monitor_height / TILE_SIZE);
}

void	ft_init_textures(t_game *game)
{
	game->textures.wall = mlx_load_png("./textures/Wall.png");
	game->textures.floor = mlx_load_png("./textures/Floor.png");
	game->textures.collectible = mlx_load_png("./textures/Collectible.png");
	game->textures.exit_closed = mlx_load_png("./textures/Exit_closed.png");
	game->textures.exit_open = mlx_load_png("./textures/Exit_open.png");
	game->textures.player_up = mlx_load_png("./textures/Player_up.png");
	game->textures.player_down = mlx_load_png("./textures/Player_down.png");
	game->textures.player_left = mlx_load_png("./textures/Player_left.png");
	game->textures.player_right = mlx_load_png("./textures/Player_right.png");
}

void	ft_init_game(t_game *game, t_map *map)
{
	game->map = map;
	game->mlx = NULL;
	game->moves = 0;
	game->player_dir = 'D';
}

t_error	ft_check_extension(const char *str)
{
	int		i;

	i = 0;
	if (! str || ft_strlen(str) < 5)
		return (ERR_FILE_PATH_INVALID);
	while (str[i] != '\0')
		i++;
	i--;
	if (str[i] != 'r' || str[i - 1] != 'e' || str[i - 2] != 'b'
		|| str[i - 3] != '.')
		return (ERR_EXTENSION_INVALID);
	return (ERR_NONE);
}

void	ft_system_error_handling(t_error error_code, const char *ctxt)
{
	if (ctxt)
	{
		if (error_code == ERR_OPEN_FILE)
			ft_printf("Error opening file '%s': %s\n", ctxt, strerror(errno));
		else if (error_code == ERR_READ_FILE)
			ft_printf("Error reading file '%s': %s\n", ctxt, strerror(errno));
		else if (error_code == ERR_SYSTEM)
			ft_printf("System error '%s': %s\n", ctxt, strerror(errno));
	}
	else
	{
		if (error_code == ERR_OPEN_FILE)
			perror("Error opening file");
		else if (error_code == ERR_READ_FILE)
			perror("Error reading file");
		else if (error_code == ERR_SYSTEM)
			perror("System error");
	}
}

void	ft_map_error_handling(t_error error_code)
{
	if (error_code == ERR_FILE_PATH_INVALID)
		ft_printf("The file path is invalid or too short.\n");
	else if (error_code == ERR_EXTENSION_INVALID)
		ft_printf("The file extension is not '.ber'.\n");
	else if (error_code == ERR_MAP_INVALID)
		ft_printf("The map is empty, invalid or wrongly formatted.\n");
	else if (error_code == ERR_PLAYER)
		ft_printf("Invalid 'P' count (must be 1).\n");
	else if (error_code == ERR_EXIT)
		ft_printf("Invalid 'E' count (must be 1).\n");
	else if (error_code == ERR_MISSING_COLLECTIBLES)
		ft_printf("Missing collectibles ('C') in the map.\n");
	else if (error_code == ERR_PATH_INVALID)
		ft_printf("The map does not have a valid path.\n");
	else if (error_code == ERR_SCREEN_LIMIT)
		ft_printf("The map is too large to be playable.\n");
	else if (error_code != ERR_SYSTEM)
		ft_printf("An unknown error occurred.\n");
}

void	ft_error_handling(t_error error_code, const char *ctxt)
{
	if (error_code == ERR_OPEN_FILE || error_code == ERR_READ_FILE
		|| error_code == ERR_SYSTEM)
	{
		ft_printf("Error\n");
		ft_system_error_handling(error_code, ctxt);
	}
	else
	{
		ft_printf("Error\n");
		ft_map_error_handling(error_code);
	}
}

int	ft_open_map_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	ft_initialize_grid(char **grid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		grid[i] = NULL;
		i++;
	}
}

char	**ft_allocate_grid(int size)
{
	char	**grid;

	if (size <= 0)
	{
		ft_map_error_handling(ERR_MAP_INVALID);
		return (NULL);
	}
	grid = malloc(size * sizeof(char *));
	if (!grid)
	{
		ft_system_error_handling(ERR_SYSTEM, NULL);
		return (NULL);
	}
	ft_initialize_grid(grid, size);
	return (grid);
}

void	ft_free_map_grid(char **grid, int line_count)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < line_count)
	{
		if (grid[i] != NULL)
		{
			free(grid[i]);
			grid[i] = NULL;
		}
		i++;
	}
	free(grid);
	grid = NULL;
}

static t_error	ft_open_and_allocate(const char *file_path, t_map *map,
	t_config *config, int *fd)
{
	*fd = ft_open_map_file(file_path);
	if (*fd == -1)
		return (ERR_OPEN_FILE);
	map->grid = ft_allocate_grid(config->max_map_height);
	if (!map->grid)
	{
		close(*fd);
		return (ERR_SYSTEM);
	}
	return (ERR_NONE);
}

static t_error	ft_handle_map_error(t_error error, t_map *map, int fd)
{
	if (map->grid != NULL)
	{
		ft_free_map_grid(map->grid, map->height);
		map->grid = NULL;
	}
	close(fd);
	return (error);
}

t_error	ft_parse_map(const char *file_path, t_map *map, t_config *config)
{
	int		fd;
	t_error	error;

	error = ft_check_extension(file_path);
	if (error != ERR_NONE)
		return (error);
	ft_init_map(map);
	error = ft_open_and_allocate(file_path, map, config, &fd);
	if (error != ERR_NONE)
		return (error);
	error = ft_read_map_lines(fd, map, config);
	close(fd);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	error = ft_validate_screen_limit(map, config);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	error = ft_validate_map(map);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	error = ft_validate_path(map);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	return (ERR_NONE);
}

static t_error	ft_validate_line(char *line, t_map *map, uint32_t line_count)
{
	size_t	line_length;

	if (!line || !map || !map->grid)
		return (ERR_MAP_INVALID);
	line_length = ft_strlen(line);
	if (line_length > 0 && line[line_length - 1] == '\n')
		line_length--;
	if (line_count == 0)
		map->width = line_length;
	else if (line_length != map->width)
		return (ERR_MAP_INVALID);
	map->grid[line_count] = ft_strdup(line);
	if (!map->grid[line_count])
		return (ERR_SYSTEM);
	return (ERR_NONE);
}

t_error	ft_process_line(char *line, t_map *map, int line_count)
{
	t_error	error;

	error = ft_validate_line(line, map, line_count);
	free(line);
	if (error != ERR_NONE)
		return (error);
	return (ERR_NONE);
}

static void	ft_cleanup_on_error(char *line, char *store_buffer, t_map *map,
		int line_count)
{
	if (line)
		free(line);
	if (store_buffer)
		free(store_buffer);
	if (map->grid)
	{
		ft_free_map_grid(map->grid, line_count);
		map->grid = NULL;
	}
}

static t_error	ft_handle_map_line(char *line, t_map *map, int *line_count)
{
	t_error	error;

	error = ft_process_line(line, map, *line_count);
	if (error == ERR_NONE)
		(*line_count)++;
	return (error);
}

static t_error	ft_finalize_map(t_map *map, int line_count)
{
	if (line_count == 0)
		return (ERR_MAP_INVALID);
	map->grid[line_count] = NULL;
	map->height = line_count;
	return (ERR_NONE);
}

t_error	ft_read_map_lines(int fd, t_map *map, t_config *config)
{
	char	*line;
	char	*store_buffer;
	int		line_count;

	store_buffer = NULL;
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd, &store_buffer);
		if (!line)
			break ;
		if (line_count >= (int)config->max_map_height)
		{
			ft_cleanup_on_error(line, store_buffer, map, line_count);
			return (ERR_SCREEN_LIMIT);
		}
		if (ft_handle_map_line(line, map, &line_count) != ERR_NONE)
		{
			ft_cleanup_on_error(NULL, store_buffer, map, line_count);
			return (ERR_MAP_INVALID);
		}
	}
	free(store_buffer);
	return (ft_finalize_map(map, line_count));
}

static t_error	ft_validate_dimensions(t_map *map)
{
	if (map->width < 3 || map->height < 3)
		return (ERR_MAP_INVALID);
	return (ERR_NONE);
}

static t_error	ft_validate_boundaries(t_map *map)
{
	uint32_t	row;

	row = 0;
	while (row < map->width)
	{
		if (map->grid[0][row] != WALL || map->grid[map->height
			- 1][row] != WALL)
			return (ERR_MAP_INVALID);
		row++;
	}
	row = 1;
	while (row < map->height - 1)
	{
		if (map->grid[row][0] != WALL || map->grid[row][map->width - 1] != WALL)
			return (ERR_MAP_INVALID);
		row++;
	}
	return (ERR_NONE);
}

t_error	ft_validate_screen_limit(t_map *map, t_config *config)
{
	if (map->width > config->max_map_width
		|| map->height > config->max_map_height)
		return (ERR_SCREEN_LIMIT);
	return (ERR_NONE);
}

t_error	ft_validate_map(t_map *map)
{
	t_error	error;

	error = ft_validate_dimensions(map);
	if (error != ERR_NONE)
		return (error);
	error = ft_validate_boundaries(map);
	if (error != ERR_NONE)
		return (error);
	error = ft_validate_characters(map);
	if (error != ERR_NONE)
		return (error);
	return (ERR_NONE);
}

static t_error	ft_count_and_validate_chars(t_map *map, uint32_t row,
		uint32_t col)
{
	if (map->grid[row][col] == PLAYER)
	{
		map->players++;
		map->player_x = col;
		map->player_y = row;
	}
	else if (map->grid[row][col] == EXIT)
		map->exits++;
	else if (map->grid[row][col] == COLLECTIBLE)
		map->collectibles++;
	else if (map->grid[row][col] != WALL && map->grid[row][col] != EMPTY)
		return (ERR_MAP_INVALID);
	return (ERR_NONE);
}

static t_error	ft_loop_grid_and_count(t_map *map)
{
	uint32_t	row;
	uint32_t	col;
	t_error		error;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			error = ft_count_and_validate_chars(map, row, col);
			if (error != ERR_NONE)
				return (error);
			col++;
		}
		row++;
	}
	return (ERR_NONE);
}

static t_error	ft_check_required_elements(t_map *map)
{
	if (map->players != 1)
		return (ERR_PLAYER);
	if (map->exits != 1)
		return (ERR_EXIT);
	if (map->collectibles == 0)
		return (ERR_MISSING_COLLECTIBLES);
	return (ERR_NONE);
}

t_error	ft_validate_characters(t_map *map)
{
	t_error	error;

	error = ft_loop_grid_and_count(map);
	if (error != ERR_NONE)
		return (error);
	error = ft_check_required_elements(map);
	if (error != ERR_NONE)
		return (error);
	return (ERR_NONE);
}

char	**ft_duplicate_grid(char **grid, uint32_t height)
{
	char		**copy;
	uint32_t	row;

	copy = malloc(height * sizeof(char *));
	if (!copy)
		return (NULL);
	row = 0;
	while (row < height)
	{
		copy[row] = ft_strdup(grid[row]);
		if (!copy[row])
		{
			ft_free_map_grid(copy, row);
			return (NULL);
		}
		row++;
	}
	return (copy);
}

//puede que sea necesario integrar la 'V' dentro de la struct como xxx->visited
void	ft_flood_fill(t_map *map, char **grid, int y, int x)
{
	if (y < 0 || y >= (int)map->height || x < 0 || x >= (int)map->width)
		return ;
	if (grid[y][x] == WALL || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == COLLECTIBLE)
		map->collectibles--;
	if (grid[y][x] == EXIT)
		map->exits--;
	grid[y][x] = 'V';
	ft_flood_fill(map, grid, y + 1, x);
	ft_flood_fill(map, grid, y - 1, x);
	ft_flood_fill(map, grid, y, x + 1);
	ft_flood_fill(map, grid, y, x - 1);
}

static t_error	ft_check_unreachable_exits(char **temp_grid, t_map *map)
{
	uint32_t	row;
	uint32_t	col;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (temp_grid[row][col] == EXIT)
				return (ERR_PATH_INVALID);
			col++;
		}
		row++;
	}
	return (ERR_NONE);
}

t_error	ft_validate_path(t_map *map)
{
	char	**temp_grid;
	t_error	error;

	temp_grid = ft_duplicate_grid(map->grid, map->height);
	if (!temp_grid)
		return (ERR_SYSTEM);
	ft_flood_fill(map, temp_grid, map->player_y, map->player_x);
	error = ft_check_unreachable_exits(temp_grid, map);
	if (error != ERR_NONE || map->collectibles > 0)
	{
		ft_free_map_grid(temp_grid, map->height);
		return (ERR_PATH_INVALID);
	}
	ft_free_map_grid(temp_grid, map->height);
	return (ERR_NONE);
}

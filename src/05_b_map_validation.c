

#include "so_long.h"

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
		return (ERR_MISSING_PLAYER);
	if (map->exits == 0)
		return (ERR_MISSING_EXIT);
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

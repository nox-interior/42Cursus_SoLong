/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_path_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:14:20 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/29 11:19:39 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_flood_fill(t_flood *flood, char **grid, int y, int x)
{
	if (y < 0 || y >= (int)flood->map->height || x < 0
		|| x >= (int)flood->map->width)
		return ;
	if (grid[y][x] == WALL || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == COLLECTIBLE)
		flood->reachable.collectibles++;
	if (grid[y][x] == EXIT)
		flood->reachable.exits++;
	grid[y][x] = 'V';
	ft_flood_fill(flood, grid, y + 1, x);
	ft_flood_fill(flood, grid, y - 1, x);
	ft_flood_fill(flood, grid, y, x + 1);
	ft_flood_fill(flood, grid, y, x - 1);
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


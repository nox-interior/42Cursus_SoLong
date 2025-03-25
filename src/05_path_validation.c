/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_path_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:14:20 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/25 10:37:48 by amarroyo         ###   ########.fr       */
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
		return;
	if (grid[y][x] == WALL || grid[y][x] == 'V')
		return;
	if (grid[y][x] == COLLECTIBLE)
		flood->reachable.collectibles++;
	if (grid[y][x] == EXIT)
		flood->reachable.exits++;
	grid[y][x] = 'V';
	if (y + 1 < (int)flood->map->height && grid[y + 1][x] != 'V')
		ft_flood_fill(flood, grid, y + 1, x);
	if (y - 1 >= 0 && grid[y - 1][x] != 'V')
		ft_flood_fill(flood, grid, y - 1, x);
	if (x + 1 < (int)flood->map->width && grid[y][x + 1] != 'V')
		ft_flood_fill(flood, grid, y, x + 1);
	if (x - 1 >= 0 && grid[y][x - 1] != 'V')
		ft_flood_fill(flood, grid, y, x - 1);
}

t_error	ft_validate_path(t_map *map)
{
	char	**temp_grid;
	t_flood	flood;

	temp_grid = ft_duplicate_grid(map->grid, map->height);
	if (!temp_grid)
		return (ERR_SYSTEM);
	flood.map = map;
	flood.reachable.collectibles = 0;
	flood.reachable.exits = 0;
	ft_flood_fill(&flood, temp_grid, map->player_y, map->player_x);
	if (flood.reachable.collectibles != map->collectibles
		|| flood.reachable.exits != map->exits)
	{
		ft_free_map_grid(temp_grid, map->height);
		return (ERR_PATH_INVALID);
	}
	ft_free_map_grid(temp_grid, map->height);
	return (ERR_NONE);
}

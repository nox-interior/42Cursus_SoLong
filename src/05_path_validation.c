/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_path_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:14:20 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/20 16:26:51 by amarroyo         ###   ########.fr       */
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

void	ft_flood_fill(t_map *map, char **grid, int start_y, int start_x)
{
	t_point	stack[map->width * map->height]; //FOrbiden variable array
	int		top;
	t_point	p;

	top = -1;
	stack[++top] = (t_point){start_x, start_y};
	while (top >= 0)
	{
		p = stack[top--];
		if (p.y < 0 || p.y >= (int)map->height || p.x < 0
			|| p.x >= (int)map->width)
			continue ;
		if (grid[p.y][p.x] == WALL || grid[p.y][p.x] == 'V')
			continue ;
		if (grid[p.y][p.x] == COLLECTIBLE)
			map->collectibles--;
		if (grid[p.y][p.x] == EXIT)
			map->exits--;
		grid[p.y][p.x] = 'V';
		if (p.x + 1 < (int)map->width)
			stack[++top] = (t_point){p.x + 1, p.y};
		if (p.x - 1 >= 0)
			stack[++top] = (t_point){p.x - 1, p.y};
		if (p.y + 1 < (int)map->height)
			stack[++top] = (t_point){p.x, p.y + 1};
		if (p.y - 1 >= 0)
			stack[++top] = (t_point){p.x, p.y - 1};
	}
}

// void ft_flood_fill(t_map *map, char **grid, int start_y, int start_x)
// {
//     typedef struct { int x, y; } t_point;

//     t_point stack[map->width * map->height];
//     int     top = -1;

//     stack[++top] = (t_point){start_x, start_y};

//     while (top >= 0)
//     {
//         t_point p = stack[top--];

//         if (p.y < 0 || p.y >= (int)map->height || p.x < 0
//	|| p.x >= (int)map->width)
//             continue ;
//         if (grid[p.y][p.x] == WALL || grid[p.y][p.x] == 'V')
//             continue ;

//         if (grid[p.y][p.x] == COLLECTIBLE)
//             map->collectibles--;
//         if (grid[p.y][p.x] == EXIT)
//             map->exits--;

//         grid[p.y][p.x] = 'V';

//         stack[++top] = (t_point){p.x + 1, p.y};
//         stack[++top] = (t_point){p.x - 1, p.y};
//         stack[++top] = (t_point){p.x, p.y + 1};
//         stack[++top] = (t_point){p.x, p.y - 1};
//     }
// }

// void	ft_flood_fill(t_map *map, char **grid, int y, int x)
// {
// 	if (y < 0 || y >= (int)map->height || x < 0 || x >= (int)map->width)
// 		return ;
// 	if (grid[y][x] == WALL || grid[y][x] == 'V')
// 		return ;
// 	if (grid[y][x] == COLLECTIBLE)
// 		map->collectibles--;
// 	if (grid[y][x] == EXIT)
// 		map->exits--;
// 	grid[y][x] = 'V';
// 	ft_flood_fill(map, grid, y + 1, x);
// 	ft_flood_fill(map, grid, y - 1, x);
// 	ft_flood_fill(map, grid, y, x + 1);
// 	ft_flood_fill(map, grid, y, x - 1);
// }

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
